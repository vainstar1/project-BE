// Custom Game settings panel: hides the rows that don't apply to player-hosted games (Spectators, Run as Dedicated
// Server) and adds rule rows built from the game's own option widget (Widget_ShifterOption_C), so they look and
// behave exactly like the rows Ninja Theory placed there.
#include <windows.h>
#include <vector>
#include "uobj.h"
#include "mod.h"

namespace settings {
namespace {
// MBOptionWidget fields
constexpr size_t OW_OptionName = 0x330, OW_IsTextValue = 0x361, OW_TextOptions = 0x368, OW_Min = 0x3a0, OW_Max = 0x3a4, OW_Index = 0x3b0;

uo::UObject* gBox;                 // the settings scroll box we decorated
uo::UObject* gRows[4];             // team size, score, objectives, capture

bool Visible(uo::UObject* w) { uo::Call c(w, L"GetParent"); return c.ok() && c.run().get<uo::UObject*>(L"ReturnValue"); }

// The designer-placed Spectators row of the settings panel on screen (its parent is the rows' scroll box).
uo::UObject* SpectatorsRow() {
    uo::UObject* cls = uo::FindClass(L"Widget_ShifterOption_C");
    for (uo::UObject* w : uo::FindAllTransient(cls)) {
        if (uo::Name(w) != L"Shifter_Spectators") continue;
        // ...inside a Custom Game screen that is on screen
        for (uo::UObject* o = uo::OuterOf(w); o; o = uo::OuterOf(o))
            if (uo::Name(uo::ClassOf(o)) == L"CustomGameScreen_C") { if (Visible(o)) return w; break; }
    }
    return nullptr;
}
uo::UObject* Sibling(uo::UObject* box, const wchar_t* name) {
    uo::Call n(box, L"GetChildrenCount"); int count = n.run().get<int32_t>(L"ReturnValue");
    for (int i = 0; i < count; i++) {
        uo::Call c(box, L"GetChildAt"); c.set<int32_t>(L"Index", i).run();
        uo::UObject* w = c.get<uo::UObject*>(L"ReturnValue");
        if (w && uo::Name(w) == name) return w;
    }
    return nullptr;
}

uo::UObject* MakeRow(uo::UObject* box, uo::UObject* rowClass, const wchar_t* label, const wchar_t* const* opts, int n, int cur) {
    uo::UObject* lib = uo::FindFirst(uo::FindClass(L"WidgetBlueprintLibrary"), true);
    if (!lib) return nullptr;
    uo::Call c(lib, L"Create");
    c.set<uo::UObject*>(L"WorldContextObject", (uo::UObject*)net::World()).set<uo::UObject*>(L"WidgetType", rowClass).set<uo::UObject*>(L"OwningPlayer", nullptr).run();
    uo::UObject* w = c.get<uo::UObject*>(L"ReturnValue");
    if (!w) return nullptr;
    uo::MakeText((uo::FText*)(w + OW_OptionName), label);
    F<bool>(w, OW_IsTextValue) = true;
    auto& arr = F<TArray<uo::FText>>(w, OW_TextOptions);
    arr.Data = (uo::FText*)uo::Malloc(sizeof(uo::FText) * n);
    for (int i = 0; i < n; i++) uo::MakeText(&arr.Data[i], opts[i]);
    arr.Num = arr.Max = n;
    F<int32_t>(w, OW_Min) = 0; F<int32_t>(w, OW_Max) = n - 1; F<int32_t>(w, OW_Index) = cur;
    uo::Call(box, L"AddChild").set<uo::UObject*>(L"Content", w).run();
    uo::Call(w, L"InitialiseWidget").set<int32_t>(L"InitialIndex", cur).run();
    uo::Call(w, L"UpdateWidget").run();
    return w;
}

void Decorate(uo::UObject* spectators) {
    uo::Call p(spectators, L"GetParent");
    uo::UObject* box = p.run().get<uo::UObject*>(L"ReturnValue");
    if (!box) return;
    gBox = box;
    for (uo::UObject* hide : { spectators, Sibling(box, L"Tickbox_Server") })
        if (hide) uo::Call(hide, L"SetVisibility").set<uint8_t>(L"InVisibility", 1).run();   // Collapsed
    rules::Values v = rules::Current();
    uo::UObject* cls = uo::ClassOf(spectators);
    int n;
    const wchar_t* const* o;
    o = rules::TeamSizeOptions(&n);  gRows[0] = MakeRow(box, cls, L"Team Size", o, n, v.teamSize - 1);
    o = rules::ScoreOptions(&n);     gRows[1] = MakeRow(box, cls, L"Score", o, n, v.score);
    o = rules::ObjectiveOptions(&n); gRows[2] = MakeRow(box, cls, L"Objectives", o, n, v.objectives);
    o = rules::CaptureOptions(&n);   gRows[3] = MakeRow(box, cls, L"Capturing", o, n, v.capture);
    Log("settings: rows added to %p", box);
}
}  // namespace

void DevAddRow() {
    if (!gBox) return;
    int n; const wchar_t* const* o = rules::ScoreOptions(&n);
    uo::UObject* sp = SpectatorsRow();
    MakeRow(gBox, sp ? uo::ClassOf(sp) : uo::FindClass(L"Widget_ShifterOption_C"), L"Dev Row", o, n, 3);
    Log("settings: dev row added");
}

void Tick() {
    if (!lobby::IsHost() || !net::MenuSettled()) return;
    static DWORD last;
    DWORD now = GetTickCount();
    if (now - last < 300) return;
    last = now;
    if (!gBox || !uo::IsLive(gBox) || !Visible(gBox)) {
        gBox = nullptr;
        for (auto& r : gRows) r = nullptr;
        // Add our rows the first time the panel is open (rows added while it is collapsed never draw their values).
        if (uo::UObject* sp = SpectatorsRow()) {
            uo::UObject* menu = nullptr;
            for (uo::UObject* o = uo::OuterOf(sp); o; o = uo::OuterOf(o))
                if (uo::Name(uo::ClassOf(o)) == L"CustomGameSettingsMenu_C") { menu = o; break; }
            // ...and once its opening transition is over: rows added while it opens never show their values.
            static DWORD openSince;
            uo::Call c(menu ? menu : sp, L"IsVisible");
            bool open = menu && c.ok() && c.run().get<bool>(L"ReturnValue");
            if (!open) openSince = 0;
            else if (!openSince) openSince = now;
            else if (now - openSince > 500) { openSince = 0; Decorate(sp); }
        }
        if (!gBox) return;
    }
    rules::Values v = rules::Current();
    if (gRows[0] && uo::IsLive(gRows[0])) v.teamSize = F<int32_t>(gRows[0], OW_Index) + 1;
    if (gRows[1] && uo::IsLive(gRows[1])) v.score = F<int32_t>(gRows[1], OW_Index);
    if (gRows[2] && uo::IsLive(gRows[2])) v.objectives = F<int32_t>(gRows[2], OW_Index);
    if (gRows[3] && uo::IsLive(gRows[3])) v.capture = F<int32_t>(gRows[3], OW_Index);
    rules::Values old = rules::Current();
    if (v.teamSize != old.teamSize) lobby::SetTeamSize(v.teamSize);
    rules::Set(v);
}
}  // namespace settings
