// Front-end integration: main menu entry, native system messages, busy spinner, Blueprint event interception.
#include <windows.h>
#include <vector>
#include <functional>
#include <cstdio>
#include "MinHook.h"
#include "uobj.h"
#include "mod.h"

namespace ui {
namespace {
// ---- Blueprint event interception ---------------------------------------------------------------------------
// We replace UFunction::Func of the hooked functions with one thunk. Every call that goes through
// UFunction::Invoke (ProcessEvent, delegates, native-to-script events) lands here; FFrame::Node tells which function.
// Handlers get the parameter block (FFrame::Locals) and return true to swallow the call (script events only).
struct FFrame { void* vt; uint8_t pad[8]; uo::UObject* Node; uo::UObject* Object; uint8_t* Code; uint8_t* Locals; };
using NativeFn = void(__fastcall*)(uo::UObject*, FFrame*, void*);
struct EventHook { std::wstring cls, fn; uo::UObject* func; std::function<bool(uo::UObject*, void*)> h; };
std::vector<EventHook> gHooks;
struct Patched { uo::UObject* func; NativeFn orig; size_t hook; };
std::vector<Patched> gPatched;   // every UFunction we ever redirected (old copies may still run during map changes)

void __fastcall FuncThunk(uo::UObject* ctx, FFrame* st, void* res) {
    for (auto& p : gPatched) {
        if (p.func != st->Node) continue;
        auto& h = gHooks[p.hook];
        if (h.func == p.func && h.h(ctx, st->Locals)) return;
        p.orig(ctx, st, res);
        return;
    }
}
void OnEvent(const wchar_t* cls, const wchar_t* fn, std::function<bool(uo::UObject*, void*)> h) { gHooks.push_back({ cls, fn, nullptr, h }); }
void ResolveHooks() {
    for (size_t i = 0; i < gHooks.size(); i++) {
        auto& h = gHooks[i];
        if (h.func && uo::IsLive(h.func) && uo::Name(h.func) == h.fn && F<void*>(h.func, uo::Func_Native) == (void*)&FuncThunk) continue;
        uo::UObject* c = uo::FindClass(h.cls.c_str());
        uo::UObject* f = c ? uo::FindFunction(c, h.fn.c_str(), true) : nullptr;
        h.func = f;
        if (!f) continue;
        NativeFn cur = F<NativeFn>(f, uo::Func_Native);
        if (cur == &FuncThunk) continue;
        // Forget patches of functions whose memory got reused.
        for (auto it = gPatched.begin(); it != gPatched.end();) it = it->func == f ? gPatched.erase(it) : it + 1;
        gPatched.push_back({ f, cur, i });
        F<NativeFn>(f, uo::Func_Native) = &FuncThunk;
        Log("ui: hooked %ls.%ls", h.cls.c_str(), h.fn.c_str());
    }
}

// ---- helpers ------------------------------------------------------------------------------------------------
void SetText(uo::UObject* tb, const wchar_t* s) {
    uo::FText t; uo::MakeText(&t, s);
    uo::Call(tb, L"SetText").set(L"InText", t).run();
}
std::wstring GetText(uo::UObject* tb) {
    uo::Call c(tb, L"GetText");
    c.run();
    uo::FText t = c.get<uo::FText>(L"ReturnValue");
    // FText -> string through Kismet: Conv_TextToString
    uo::UObject* lib = uo::FindFirst(uo::FindClass(L"KismetTextLibrary"), true);
    if (!lib) return L"";
    uo::Call k(lib, L"Conv_TextToString");
    k.set(L"InText", t).run();
    FString s = k.get<FString>(L"ReturnValue");
    return s.c_str();
}
uo::UObject* WidgetNamed(uo::UObject* cls, const wchar_t* outerName, const wchar_t* name) {
    FName want = uo::MakeName(name);
    for (uo::UObject* w : uo::FindAll(cls)) {
        if (!uo::NameIs(w, want)) continue;
        // WidgetTree_0 -> owning user widget
        uo::UObject* tree = uo::OuterOf(w);
        uo::UObject* owner = tree ? uo::OuterOf(tree) : nullptr;
        if (owner && !uo::IsDefault(owner) && uo::Name(uo::ClassOf(owner)) == outerName) return w;
    }
    return nullptr;
}

uo::UObject* TopScreen() {
    uo::UObject* main = uo::FindTransient(uo::FindClass(L"FE_MainMenuScreen_C"));
    return main;
}

void RelabelMenu() {
    uo::UObject* tb = uo::FindClass(L"TextBlock");
    if (!tb) return;
    for (const wchar_t* n : { L"CustomQueueText", L"TextBlock_0" }) {
        uo::UObject* w = WidgetNamed(tb, L"FE_BillboardMainMenu_C", n);
        if (w && GetText(w) == L"CUSTOM QUEUE") SetText(w, L"CUSTOM GAME");
    }
    // When an update was postponed, the billboard's "Leaderboards" line (dead without the official servers)
    // becomes "Update".
    if (update::Available() && update::Postponed()) {
        uo::UObject* t = WidgetNamed(tb, L"FE_BillboardMainMenu_C", L"LeaderboardsText");
        if (t && GetText(t) != L"Update") SetText(t, L"Update");
    }
}
}  // namespace

void ShowMessage(const std::wstring& title, const std::wstring& body) {
    uo::UObject* mgrCls = uo::FindClass(L"MBSystemMessageManager");
    uo::UObject* cdo = mgrCls ? uo::FindFirst(mgrCls, true) : nullptr;
    uo::UObject* world = nullptr;
    if (uo::UObject* gi = uo::FindFirst(uo::FindClass(L"MBGameInstance"))) world = gi;
    if (!cdo || !world) { Log("ui: can't show message '%ls'", body.c_str()); return; }
    uo::FText t; uo::MakeText(&t, body.c_str());
    uo::Call c(cdo, L"ShowSystemMessageText");
    c.set(L"MessageText", t).set(L"MessageId", uo::MakeName(L"BE1v1Message")).set<uo::UObject*>(L"WorldContextObject", world).run();
    Log("ui: message '%ls'", body.c_str());
    (void)title;
}

// ---- Prompts and lists on the game's own system message screen (torn-paper banner) ----------------------------
// A prompt shows a message and two buttons; a list prompt adds a column of the game's PromptListButtonTemplate
// buttons (the pause menu's buttons) between them. Result: row index, kYes or kNo.
namespace {
struct Prompt {
    std::wstring body, yes, no; std::vector<std::wstring> rows; std::function<void(int)> cb;
    uo::UObject* screen; DWORD shownAt; bool labelled; int choice; std::vector<uo::UObject*> rowWidgets; int focusPending = 0; int focused = -1;
};
std::vector<Prompt> gPrompts;   // front = showing
constexpr size_t SMS_MessageResult = 0x450;
constexpr size_t PLB_ButtonTextProp = 0x4e0;

uo::UObject* GameInstance() { return uo::FindTransient(uo::FindClass(L"MBGameInstance")); }
bool Inside(uo::UObject* w, uo::UObject* root) { for (uo::UObject* o = uo::OuterOf(w); o; o = uo::OuterOf(o)) if (o == root) return true; return false; }
uo::UObject* Child(uo::UObject* root, const wchar_t* cls, const wchar_t* name) {
    FName want = uo::MakeName(name);
    for (uo::UObject* w : uo::FindAll(uo::FindClass(cls))) if (uo::NameIs(w, want) && Inside(w, root)) return w;
    return nullptr;
}

bool ShowPromptNow(Prompt& p) {
    uo::UObject* mgrCls = uo::FindClass(L"MBSystemMessageManager");
    uo::UObject* cdo = mgrCls ? uo::FindFirst(mgrCls, true) : nullptr;
    uo::UObject* scrCls = uo::FindClass(L"DefaultYesNoSystemMessageScreen_C");
    uo::UObject* gi = GameInstance();
    if (!cdo || !scrCls || !gi) { Log("ui: prompt unavailable (mgr=%p cls=%p gi=%p)", cdo, scrCls, gi); return false; }
    uo::Call c(cdo, L"ShowSystemMessageInfo");
    int info = c.off(L"Info");
    if (info < 0) return false;
    uo::MakeText((uo::FText*)(c.buf.data() + info), p.body.empty() ? L" " : p.body.c_str());
    *(int32_t*)(c.buf.data() + info + 0x18) = 100;                // Priority
    *(uo::UObject**)(c.buf.data() + info + 0x20) = scrCls;          // MessageScreenClass
    c.set(L"MessageId", uo::MakeName(L"BE1v1Prompt")).set<uo::UObject*>(L"WorldContextObject", gi).run();
    p.shownAt = GetTickCount(); p.screen = nullptr; p.labelled = false; p.choice = kNo; p.rowWidgets.clear();
    Log("ui: prompt '%ls' (%d rows)", p.body.c_str(), (int)p.rows.size());
    return true;
}

// Adds the list rows between the message and the buttons.
void AddRows(Prompt& p) {
    uo::UObject* box = Child(p.screen, L"VerticalBox", L"VerticalBox_2");
    uo::UObject* buttons = Child(p.screen, L"SizeBox", L"SizeBox_0");
    uo::UObject* rowCls = uo::FindClass(L"PromptListButtonTemplate_C");
    uo::UObject* lib = uo::FindFirst(uo::FindClass(L"WidgetBlueprintLibrary"), true);
    if (!box || !buttons || !rowCls || !lib) { Log("ui: list layout not found"); return; }
    if (p.body.empty()) if (uo::UObject* tb = Child(p.screen, L"Border", L"TextBorder")) uo::Call(tb, L"SetVisibility").set<uint8_t>(L"InVisibility", 1).run();
    uo::Call(box, L"RemoveChild").set<uo::UObject*>(L"Content", buttons).run();
    for (auto& r : p.rows) {
        uo::Call c(lib, L"Create");
        c.set<uo::UObject*>(L"WorldContextObject", (uo::UObject*)net::World()).set<uo::UObject*>(L"WidgetType", rowCls).set<uo::UObject*>(L"OwningPlayer", nullptr).run();
        uo::UObject* w = c.get<uo::UObject*>(L"ReturnValue");
        if (!w) continue;
        uo::MakeText((uo::FText*)(w + PLB_ButtonTextProp), r.c_str());
        F<int32_t>(w, 0x760) = 20;     // TextSize, as the pause menu's list
        uo::Call add(box, L"AddChild");
        uo::UObject* slot = add.set<uo::UObject*>(L"Content", w).run().get<uo::UObject*>(L"ReturnValue");
        if (slot) uo::Call(slot, L"SetHorizontalAlignment").set<uint8_t>(L"InHorizontalAlignment", 2).run();   // centred
        p.rowWidgets.push_back(w);
    }
    // A list without bottom buttons looks like the pause menu; Escape / B closes it.
    if (!p.yes.empty() || !p.no.empty()) uo::Call(box, L"AddChild").set<uo::UObject*>(L"Content", buttons).run();
    p.focusPending = 2;
}

// Renames the Yes/No buttons of the prompt screen to our labels (and hides "yes" when it has no label).
void LabelPrompt(Prompt& p) {
    uo::UObject* tb = uo::FindClass(L"TextBlock");
    int done = 0;
    for (uo::UObject* w : uo::FindAllTransient(tb)) {
        if (!Inside(w, p.screen)) continue;
        std::wstring t = GetText(w);
        if (t == L"YES" || t == L"Yes") { SetText(w, p.yes.c_str()); done++; }
        else if (t == L"NO" || t == L"No") { SetText(w, p.no.c_str()); done++; }
    }
    if (p.yes.empty()) if (uo::UObject* y = Child(p.screen, L"ButtonTemplate_C", L"YesButton")) uo::Call(y, L"SetVisibility").set<uint8_t>(L"InVisibility", 1).run();
    p.labelled = done > 0;
    if (p.labelled && !p.rows.empty()) AddRows(p);
}

void ClosePrompt(Prompt& p) {
    if (p.screen && uo::IsLive(p.screen)) uo::Call(p.screen, L"OnNoResult").run();
}

void TickPrompts() {
    if (gPrompts.empty()) return;
    Prompt& p = gPrompts.front();
    if (!p.shownAt) { if (!ShowPromptNow(p)) { gPrompts.erase(gPrompts.begin()); } return; }
    if (!p.screen) {
        for (uo::UObject* s : uo::FindAllTransient(uo::FindClass(L"DefaultYesNoSystemMessageScreen_C"))) {
            uo::Call par(s, L"GetParent");
            if (par.ok() && par.run().get<uo::UObject*>(L"ReturnValue")) { p.screen = s; break; }
        }
        if (!p.screen && GetTickCount() - p.shownAt > 10000) { Log("ui: prompt never appeared"); gPrompts.erase(gPrompts.begin()); }
        return;
    }
    if (!p.labelled) LabelPrompt(p);
    // Keyboard / controller focus on the first row once the rows exist (focusing the row's inner button lets the
    // arrow keys and the d-pad move through the list).
    if (p.focusPending > 0 && --p.focusPending == 0 && !p.rowWidgets.empty() && uo::IsLive(p.rowWidgets[0]))
        if (uo::UObject* b = F<uo::UObject*>(p.rowWidgets[0], 0x4a0)) uo::Call(b, L"SetKeyboardFocus").run();
    uo::Call par(p.screen, L"GetParent");
    bool open = uo::IsLive(p.screen) && par.ok() && par.run().get<uo::UObject*>(L"ReturnValue");
    if (open) {
        // Remember the focused row: the keyboard/controller "accept" goes to the banner, which reports "yes".
        for (size_t i = 0; i < p.rowWidgets.size(); i++) {
            uo::UObject* b = uo::IsLive(p.rowWidgets[i]) ? F<uo::UObject*>(p.rowWidgets[i], 0x4a0) : nullptr;
            uo::Call f(b, L"HasKeyboardFocus");
            if (b && f.ok() && f.run().get<bool>(L"ReturnValue")) p.focused = (int)i;
        }
        return;
    }
    uint8_t result = uo::IsLive(p.screen) ? F<uint8_t>(p.screen, SMS_MessageResult) : 0;
    int choice = p.choice >= 0 ? p.choice : (result == 1 ? kYes : kNo);
    if (choice == kYes && !p.rowWidgets.empty() && p.yes.empty()) choice = p.focused >= 0 ? p.focused : 0;
    Log("ui: prompt closed, choice=%d", choice);
    auto cb = p.cb;
    gPrompts.erase(gPrompts.begin());
    if (cb) cb(choice);
}

// A list row was pressed (mouse click, Enter or the controller's A button).
bool OnRowPressed(uo::UObject* btn) {
    if (gPrompts.empty()) return false;
    Prompt& p = gPrompts.front();
    for (size_t i = 0; i < p.rowWidgets.size(); i++) {
        if (p.rowWidgets[i] != btn) continue;
        p.choice = (int)i;
        ClosePrompt(p);
        return true;
    }
    return false;
}
}  // namespace

void Ask(const std::wstring& body, const std::wstring& yes, const std::wstring& no, std::function<void(bool)> cb) {
    gPrompts.push_back(Prompt{ body, yes, no, {}, [cb](int c) { if (cb) cb(c == kYes); }, nullptr, 0, false, kNo, {} });
}
void List(const std::wstring& body, const std::vector<std::wstring>& rows, const std::wstring& yes, const std::wstring& no, std::function<void(int)> cb) {
    gPrompts.push_back(Prompt{ body, yes, no, rows, cb, nullptr, 0, false, kNo, {} });
}
bool PromptOpen() { return !gPrompts.empty(); }

std::wstring TextToString(const void* ftext) {
    uo::UObject* lib = uo::FindFirst(uo::FindClass(L"KismetTextLibrary"), true);
    if (!lib || !ftext) return L"";
    uo::Call k(lib, L"Conv_TextToString");
    k.set(L"InText", *(const uo::FText*)ftext).run();
    FString s = k.get<FString>(L"ReturnValue");
    return s.c_str();
}

bool MainMenuReady() {
    uo::UObject* m = uo::FindTransient(uo::FindClass(L"FE_MainMenuScreen_C"));
    uo::UObject* s = uo::FindTransient(uo::FindClass(L"FE_StartScreen_C"));
    auto visible = [](uo::UObject* w) { uo::Call c(w, L"IsVisible"); return c.ok() && c.run().get<bool>(L"ReturnValue"); };
    return m && visible(m) && !(s && visible(s)) && gPrompts.empty() && net::MenuSettled();
}

void ShowBusy(bool on) {
    uo::UObject* s = TopScreen();
    if (!s) return;
    if (on) uo::Call(s, L"SetBusyWaiting").set(L"TimeOut", 15.0f).set(L"bClearFocus", true).run();
    else uo::Call(s, L"ClearBusyWaiting").run();
}

void Tick(float dt) {
    static float acc;
    acc += dt;
    if (acc < 1.0f) return;
    acc = 0;
    if (!net::MenuSettled()) return;
    ResolveHooks();
    RelabelMenu();
}

// Prompts tick faster so list rows appear right after the banner opens.
void FastTick() {
    static DWORD last;
    DWORD now = GetTickCount();
    if (now - last < 100) return;
    last = now;
    if (net::MenuSettled()) TickPrompts();
}

void DevCommand(const char* cmd) {
    if (!strcmp(cmd, "ask")) Ask(L"Test prompt body.", L"UPDATE", L"LATER", [](bool y) { Log("ui: dev prompt answered %d", y); });
    if (!strcmp(cmd, "msg")) ShowMessage(L"", L"Test message.");
    if (!strcmp(cmd, "addrow")) settings::DevAddRow();
    // Simulated clicks (the same UFunction calls a real button press makes).
    char arg[128] = {}; int team = 0;
    if (sscanf(cmd, "press %127s", arg) == 1) {
        std::wstring want = Utf8ToWide(arg);
        for (uo::UObject* b : uo::FindAll(uo::FindClass(L"PromptListButtonTemplate_C"))) {
            if (uo::Name(b) != want) continue;
            uo::Call par(b, L"GetParent");
            if (!par.ok() || !par.run().get<uo::UObject*>(L"ReturnValue")) continue;
            Log("ui: dev press %ls", want.c_str());
            uo::Call(b, L"BndEvt__ButtonOverlay_K2Node_ComponentBoundEvent_145_OnButtonPressedEvent__DelegateSignature").run();
            break;
        }
    }
    if (sscanf(cmd, "slot %d %127s", &team, arg) == 2) {
        for (uo::UObject* b : uo::FindAll(uo::FindClass(L"CustomGame_PlayerSlot_Queue_C"))) {
            bool occ = F<bool>(b, 0x4a8), loc = F<bool>(b, 0x4aa);
            if (F<int32_t>(b, 0x480) != team) continue;
            if ((!strcmp(arg, "local") && loc) || (!strcmp(arg, "empty") && !occ) || (!strcmp(arg, "other") && occ && !loc)) {
                Log("ui: dev slot %d %s", team, arg);
                uo::Call(b, L"OnPressed_Event").run();
                break;
            }
        }
    }
    if (!strcmp(cmd, "hooks"))
        for (auto& h : gHooks)
            Log("ui: hook %ls.%ls func=%p native=%p thunk=%p flags=%x", h.cls.c_str(), h.fn.c_str(), h.func,
                h.func ? F<void*>(h.func, uo::Func_Native) : nullptr, (void*)&FuncThunk, h.func ? F<uint32_t>(h.func, uo::Func_Flags) : 0);
    if (!strcmp(cmd, "list")) List(L"", { L"CREATE GAME", L"ODD'S GAME   JERSEY SINK   1/8", L"REFRESH" }, L"", L"", [](int c) { Log("ui: dev list answered %d", c); });
}

void Install() {
    // Main menu: "Custom Queue" (the dead official password queue) becomes our Custom Game entry.
    OnEvent(L"FE_MainMenuScreen_C", L"OnCustomQueuePressed", [](uo::UObject*, void*) {
        Log("ui: Custom Game pressed");
        if (lobby::Active()) lobby::ShowScreen(); else lobby::OpenBrowser();
        return true;
    });
    // Rows of our list prompts, and the lobby screen's LEAVE button.
    OnEvent(L"PromptListButtonTemplate_C", L"BndEvt__ButtonOverlay_K2Node_ComponentBoundEvent_145_OnButtonPressedEvent__DelegateSignature",
            [](uo::UObject* btn, void*) { return OnRowPressed(btn) || lobby::OnListButton(btn); });
    // Lobby screen BACK / Escape: return to the main menu but stay in the lobby (LEAVE leaves).
    OnEvent(L"CustomGameScreen_C", L"BndEvt__FE_CustomGameMenu_K2Node_ComponentBoundEvent_55_OnLeaveGamePressed__DelegateSignature",
            [](uo::UObject*, void*) { return lobby::OnBackPressed(); });
    // Team slots: click to switch teams with a mouse.
    OnEvent(L"CustomGame_PlayerSlot_Queue_C", L"OnPressed_Event", [](uo::UObject* slot, void*) { return lobby::OnSlotPressed(slot); });
    OnEvent(L"FE_MainMenuScreen_C", L"OnLeaderboardButtonPressed", [](uo::UObject*, void*) {
        if (!update::Available()) return false;
        update::Begin();
        return true;
    });
    // Lobby INVITE: Steam's own invite dialog (friends list with Invite buttons) instead of the dead Xbox one.
    OnEvent(L"CustomGameScreen_C", L"BndEvt__FE_CustomGameMenu_K2Node_ComponentBoundEvent_2_OnInviteFriendPressed__DelegateSignature",
            [](uo::UObject*, void*) { lobby::OpenInvite(); return true; });
    Log("ui: installed");
}
}  // namespace ui
