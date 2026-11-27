// Custom Game settings panel: hides the row that doesn't apply to player-hosted games (Run as Dedicated Server) and
// adds rule rows built from the game's own option widgets (Widget_ShifterOption_C / Widget_TickBoxOption_C), so they
// look and behave exactly like the rows Ninja Theory placed there.
//
// Panel (host):  Privacy, Lock Teams, Spectators (the game's rows), then
//   Teams (2-4), Team Size, KOs to Win (3-4 teams), Points to Win (Objective Control), Cells to Win (Power
//   Collection), Objective Rotation, Capture Speed, Map Mods (Off / Choose / All) and, only while "Choose" is
//   selected, one on/off row per modifier. With 3-4 teams (Team Brawl: knockouts only) the objective rows are hidden.
#include <windows.h>
#include <vector>
#include <string>
#include "uobj.h"
#include "mod.h"

namespace settings {
namespace {
// MBOptionWidget fields
constexpr size_t OW_OptionName = 0x330, OW_IsTextValue = 0x361, OW_TextOptions = 0x368, OW_Min = 0x3a0, OW_Max = 0x3a4, OW_Index = 0x3b0;
enum Row { RTeams, RTeam, RScoring, RKos, RCp, RPc, RRotation, RCapture, RMods, NumRows };

uo::UObject* gBox;                 // the settings scroll box we decorated
uo::UObject* gSpecRow;             // the game's own Spectators row
uo::UObject* gRows[NumRows];
uo::UObject* gModRows[32];         // one tick box per map modifier
int gModModeShown = -1;            // mod rows visibility we last applied
int gTeamsShown = -1;              // team count the rows were last laid out for
int gScoringShown = -1;            // scoring mode the rows were last laid out for

bool OnScreen(uo::UObject* w) { uo::Call c(w, L"GetParent"); return c.ok() && c.run().get<uo::UObject*>(L"ReturnValue"); }
bool Live(uo::UObject* w) { return w && uo::IsLive(w); }
int IndexOf(uo::UObject* row) { return Live(row) ? F<int32_t>(row, OW_Index) : -1; }

// The designer-placed Spectators row of the settings panel on screen (its parent is the rows' scroll box).
uo::UObject* SpectatorsRow() {
    uo::UObject* cls = uo::FindClass(L"Widget_ShifterOption_C");
    static FName want = uo::MakeName(L"Shifter_Spectators");
    for (uo::UObject* w : uo::FindAll(cls)) {
        if (!uo::NameIs(w, want)) continue;
        for (uo::UObject* o = uo::OuterOf(w); o; o = uo::OuterOf(o))
            if (uo::Name(uo::ClassOf(o)) == L"CustomGameScreen_C") { if (OnScreen(o)) return w; break; }
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

uo::UObject* MakeRow(uo::UObject* box, uo::UObject* rowClass, const wchar_t* label, const std::vector<std::wstring>& opts, int cur) {
    uo::UObject* lib = uo::FindFirst(uo::FindClass(L"WidgetBlueprintLibrary"), true);
    if (!lib || opts.empty()) return nullptr;
    uo::Call c(lib, L"Create");
    c.set<uo::UObject*>(L"WorldContextObject", (uo::UObject*)net::World()).set<uo::UObject*>(L"WidgetType", rowClass).set<uo::UObject*>(L"OwningPlayer", nullptr).run();
    uo::UObject* w = c.get<uo::UObject*>(L"ReturnValue");
    if (!w) return nullptr;
    int n = (int)opts.size();
    if (cur < 0 || cur >= n) cur = 0;
    uo::MakeText((uo::FText*)(w + OW_OptionName), label);
    F<bool>(w, OW_IsTextValue) = true;
    auto& arr = F<TArray<uo::FText>>(w, OW_TextOptions);
    arr.Data = (uo::FText*)uo::Malloc(sizeof(uo::FText) * n);
    for (int i = 0; i < n; i++) uo::MakeText(&arr.Data[i], opts[i].c_str());
    arr.Num = arr.Max = n;
    F<int32_t>(w, OW_Min) = 0; F<int32_t>(w, OW_Max) = n - 1; F<int32_t>(w, OW_Index) = cur;
    uo::Call(box, L"AddChild").set<uo::UObject*>(L"Content", w).run();
    uo::Call(w, L"InitialiseWidget").set<int32_t>(L"InitialIndex", cur).run();
    uo::Call(w, L"UpdateWidget").run();
    return w;
}
std::vector<std::wstring> List(const wchar_t* const* o, int n) { return std::vector<std::wstring>(o, o + n); }
void SetIndex(uo::UObject* row, int i) {
    if (!Live(row) || IndexOf(row) == i) return;
    uo::Call(row, L"ChangeOption").set<int32_t>(L"NewIndex", i).run();
    uo::Call(row, L"AdjustWidgetToIndex").set<int32_t>(L"NewIndex", i).run();
}
void ShowModRows(int mode) {
    if (mode == gModModeShown) return;
    gModModeShown = mode;
    for (int i = 0; i < rules::NumMods() && i < 32; i++)
        if (Live(gModRows[i])) uo::Call(gModRows[i], L"SetVisibility").set<uint8_t>(L"InVisibility", mode == 1 ? 0 : 1).run();
}

void SetVisible(uo::UObject* w, bool on) {
    if (!Live(w)) return;
    uo::Call(w, L"SetVisibility").set<uint8_t>(L"InVisibility", on ? 0 : 1).run();
}
// The team count decides which score rows apply, and how Team Size reads ("2v2" / "2v2v2" / "2v2v2v2").
void ShowTeamRows(int teams, int koOnly) {
    if (koOnly == gScoringShown && teams == gTeamsShown) return;
    if (koOnly != gScoringShown || (teams > 2) != (gTeamsShown > 2)) {
        SetVisible(gRows[RKos], koOnly != 0);
        for (Row r : { RCp, RRotation, RCapture }) SetVisible(gRows[r], !koOnly);
        SetVisible(gRows[RPc], !koOnly && teams <= 2);   // 3-4 teams play Objective Control (no cells)
    }
    gScoringShown = koOnly;
    if (teams == gTeamsShown) return;
    gTeamsShown = teams;
    uo::UObject* row = gRows[RTeam];
    if (Live(row)) {
        auto labels = rules::TeamSizeLabels(teams);
        auto& arr = F<TArray<uo::FText>>(row, OW_TextOptions);
        for (int i = 0; i < arr.Num && i < (int)labels.size(); i++) uo::MakeText(&arr.Data[i], labels[i].c_str());
        uo::Call(row, L"InitialiseWidget").set<int32_t>(L"InitialIndex", IndexOf(row)).run();   // redraws the shown value
        uo::Call(row, L"UpdateWidget").run();
    }
}

void Decorate(uo::UObject* spectators) {
    uo::Call p(spectators, L"GetParent");
    uo::UObject* box = p.run().get<uo::UObject*>(L"ReturnValue");
    if (!box) return;
    gBox = box;
    if (uo::UObject* hide = Sibling(box, L"Tickbox_Server")) uo::Call(hide, L"SetVisibility").set<uint8_t>(L"InVisibility", 1).run();
    uo::Call(spectators, L"SetVisibility").set<uint8_t>(L"InVisibility", 0).run();   // earlier versions hid it
    // The game's Spectators row starts from its own default; show the lobby's actual number of spectator places.
    gSpecRow = spectators;
    Log("settings: spectators row text=%d min=%d max=%d index=%d, lobby has %d", F<bool>(spectators, OW_IsTextValue), F<int32_t>(spectators, OW_Min),
        F<int32_t>(spectators, OW_Max), F<int32_t>(spectators, OW_Index), lobby::SpectatorPlaces());
    SetIndex(spectators, lobby::SpectatorPlaces() - (F<bool>(spectators, OW_IsTextValue) ? 0 : F<int32_t>(spectators, OW_Min)));
    rules::Values v = rules::Current();
    uo::UObject* cls = uo::ClassOf(spectators);
    int n;
    const wchar_t* const* o;
    gRows[RTeams] = MakeRow(box, cls, L"Teams", rules::TeamCountOptions(), v.teams - 2);
    gRows[RTeam] = MakeRow(box, cls, L"Team Size", rules::TeamSizeLabels(v.teams), v.teamSize - 1);
    gRows[RScoring] = MakeRow(box, cls, L"Scoring", rules::ScoringOptions(), v.koOnly);
    gRows[RKos] = MakeRow(box, cls, L"KOs to Win", rules::KoOptions(), rules::KoIndex(v.kos));
    gRows[RCp] = MakeRow(box, cls, L"Points to Win", rules::CpScoreOptions(), rules::CpIndex(v.cp));
    gRows[RPc] = MakeRow(box, cls, L"Cells to Win", rules::PcScoreOptions(), rules::PcIndex(v.pc));
    o = rules::ObjectiveOptions(&n); gRows[RRotation] = MakeRow(box, cls, L"Objectives", List(o, n), v.objectives);
    o = rules::CaptureOptions(&n);   gRows[RCapture] = MakeRow(box, cls, L"Capture Speed", List(o, n), v.capture);
    o = rules::ModModeOptions(&n);   gRows[RMods] = MakeRow(box, cls, L"Map Mods", List(o, n), v.modMode);
    // One on/off row per modifier, styled like "Lock Teams"; shown only while Map Mods is "Choose".
    if (uo::UObject* tick = Sibling(box, L"Tickbox_Teams")) {
        uo::UObject* tcls = uo::ClassOf(tick);
        for (int i = 0; i < rules::NumMods() && i < 32; i++)
            gModRows[i] = MakeRow(box, tcls, rules::ModName(i), { L"Off", L"On" }, (v.mods >> i) & 1);
    }
    gModModeShown = -1;
    ShowModRows(v.modMode);
    gTeamsShown = -1; gScoringShown = -1;
    ShowTeamRows(v.teams, v.koOnly);
    Log("settings: rows added to %p", box);
}
}  // namespace

// Developer testing: "ui setrow <row> <index>" (rows: 0 teams, 1 team size, 2 scoring, 3 KOs, 4 points, 5 cells, 6 objectives, 7 capture, 8 mods,
// 10+i map mod i, 99 spectators).
void DevSetRow(int row, int index) {
    uo::UObject* r = row == 99 ? gSpecRow : row >= 10 ? (row - 10 < 32 ? gModRows[row - 10] : nullptr) : row < NumRows ? gRows[row] : nullptr;
    Log("settings: dev row %d -> %d (%p)", row, index, r);
    SetIndex(r, index);
}

void Tick() {
    if (!lobby::IsHost() || !net::MenuSettled()) return;
    static DWORD last;
    DWORD now = GetTickCount();
    if (now - last < 100) return;
    last = now;
    if (!gBox || !uo::IsLive(gBox) || !OnScreen(gBox)) {
        gBox = nullptr;
        for (auto& r : gRows) r = nullptr;
        for (auto& r : gModRows) r = nullptr;
        gSpecRow = nullptr;
        // Rows are added once the panel is open and its opening transition has settled: rows added while it is
        // collapsed or still sliding in never draw their values.
        static DWORD openSince;
        uo::UObject* sp = SpectatorsRow();
        uo::UObject* menu = nullptr;
        for (uo::UObject* o = sp ? uo::OuterOf(sp) : nullptr; o; o = uo::OuterOf(o))
            if (uo::Name(uo::ClassOf(o)) == L"CustomGameSettingsMenu_C") { menu = o; break; }
        uo::Call c(menu ? menu : sp, L"IsVisible");
        bool open = menu && c.ok() && c.run().get<bool>(L"ReturnValue");
        if (!open) openSince = 0;
        else if (!openSince) openSince = now;
        else if (now - openSince > 250) { openSince = 0; Decorate(sp); }
        if (!gBox) return;
    }
    rules::Values v = rules::Current();
    if (IndexOf(gRows[RTeams]) >= 0) v.teams = IndexOf(gRows[RTeams]) + 2;
    if (IndexOf(gRows[RTeam]) >= 0) v.teamSize = IndexOf(gRows[RTeam]) + 1;
    if (IndexOf(gRows[RKos]) >= 0) v.kos = rules::KoValueAt(IndexOf(gRows[RKos]));
    if (IndexOf(gRows[RScoring]) >= 0) v.koOnly = IndexOf(gRows[RScoring]);
    ShowTeamRows(v.teams, v.koOnly);
    if (IndexOf(gRows[RCp]) >= 0) v.cp = rules::CpValueAt(IndexOf(gRows[RCp]));
    if (IndexOf(gRows[RPc]) >= 0) v.pc = rules::PcValueAt(IndexOf(gRows[RPc]));
    if (IndexOf(gRows[RRotation]) >= 0) v.objectives = IndexOf(gRows[RRotation]);
    if (IndexOf(gRows[RCapture]) >= 0) v.capture = IndexOf(gRows[RCapture]);
    int mode = IndexOf(gRows[RMods]);
    if (mode >= 0) {
        uint32_t all = (1u << rules::NumMods()) - 1;
        if (mode != v.modMode && mode == 1) {
            // Switching to "Choose": start from what was active (everything after "All").
            uint32_t start = v.modMode == 2 ? all : v.mods;
            for (int i = 0; i < rules::NumMods() && i < 32; i++) SetIndex(gModRows[i], (start >> i) & 1);
        }
        v.modMode = mode;
        if (mode == 0) v.mods = 0;
        else if (mode == 2) v.mods = all;
        else {
            uint32_t mods = 0;
            for (int i = 0; i < rules::NumMods() && i < 32; i++) if (IndexOf(gModRows[i]) == 1) mods |= 1u << i;
            v.mods = mods;
        }
        ShowModRows(mode);
    }
    if (IndexOf(gSpecRow) >= 0) {
        int places = IndexOf(gSpecRow) + (F<bool>(gSpecRow, OW_IsTextValue) ? 0 : F<int32_t>(gSpecRow, OW_Min));
        if (places != lobby::SpectatorPlaces()) lobby::SetSpectatorPlaces(places);
    }
    rules::Values old = rules::Current();
    rules::Set(v);
    if (v.teamSize != old.teamSize || v.teams != old.teams) lobby::SetTeamSize(v.teamSize);
}
}  // namespace settings
