// Front-end integration: main menu entry, native system messages, busy spinner, Blueprint event interception.
#include <windows.h>
#include <vector>
#include <functional>
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
struct EventHook { std::wstring cls, fn; uo::UObject* func; NativeFn orig; std::function<bool(uo::UObject*, void*)> h; };
std::vector<EventHook> gHooks;

void __fastcall FuncThunk(uo::UObject* ctx, FFrame* st, void* res) {
    for (auto& h : gHooks) {
        if (h.func != st->Node) continue;
        if (h.h(ctx, st->Locals)) return;
        h.orig(ctx, st, res);
        return;
    }
}
void OnEvent(const wchar_t* cls, const wchar_t* fn, std::function<bool(uo::UObject*, void*)> h) { gHooks.push_back({ cls, fn, nullptr, nullptr, h }); }
void ResolveHooks() {
    for (auto& h : gHooks) {
        if (h.func && uo::IsLive(h.func) && F<void*>(h.func, uo::Func_Native) == (void*)&FuncThunk) continue;
        uo::UObject* c = uo::FindClass(h.cls.c_str());
        uo::UObject* f = c ? uo::FindFunction(c, h.fn.c_str(), true) : nullptr;
        if (!f) { h.func = nullptr; continue; }
        NativeFn cur = F<NativeFn>(f, uo::Func_Native);
        if (cur == &FuncThunk) continue;
        h.func = f; h.orig = cur;
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
    for (uo::UObject* w : uo::FindAllTransient(cls)) {
        if (uo::Name(w) != name) continue;
        // WidgetTree_0 -> owning user widget
        uo::UObject* tree = uo::OuterOf(w);
        uo::UObject* owner = tree ? uo::OuterOf(tree) : nullptr;
        if (owner && uo::Name(uo::ClassOf(owner)) == outerName) return w;
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
    // When an update was postponed, the billboard's unused "Report a Bug" line becomes "Update".
    if (update::Available() && update::Postponed()) {
        uo::UObject* t = WidgetNamed(tb, L"FE_BillboardMainMenu_C", L"ReportBugText");
        if (t && GetText(t) != L"UPDATE") SetText(t, L"UPDATE");
        uo::UObject* b = WidgetNamed(uo::FindClass(L"FakeButtonTemplate_C"), L"FE_BillboardMainMenu_C", L"ReportABugBTN");
        if (b) {
            uo::Call v(b, L"GetVisibility");
            if (v.ok() && v.run().get<uint8_t>(L"ReturnValue") != 0) uo::Call(b, L"SetVisibility").set<uint8_t>(L"InVisibility", 0).run();
        }
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

// ---- Yes/No prompts on the game's own system message screen --------------------------------------------------
namespace {
struct Prompt { std::wstring body, yes, no; std::function<void(bool)> cb; uo::UObject* screen; DWORD shownAt; bool labelled; };
std::vector<Prompt> gPrompts;   // front = showing
constexpr size_t SMS_MessageResult = 0x450;

uo::UObject* GameInstance() { return uo::FindTransient(uo::FindClass(L"MBGameInstance")); }

bool ShowPromptNow(Prompt& p) {
    uo::UObject* mgrCls = uo::FindClass(L"MBSystemMessageManager");
    uo::UObject* cdo = mgrCls ? uo::FindFirst(mgrCls, true) : nullptr;
    uo::UObject* scrCls = uo::FindClass(L"DefaultYesNoSystemMessageScreen_C");
    uo::UObject* gi = GameInstance();
    if (!cdo || !scrCls || !gi) { Log("ui: prompt unavailable (mgr=%p cls=%p gi=%p)", cdo, scrCls, gi); return false; }
    uo::Call c(cdo, L"ShowSystemMessageInfo");
    int info = c.off(L"Info");
    if (info < 0) return false;
    uo::MakeText((uo::FText*)(c.buf.data() + info), p.body.c_str());
    *(int32_t*)(c.buf.data() + info + 0x18) = 100;                // Priority
    *(uo::UObject**)(c.buf.data() + info + 0x20) = scrCls;          // MessageScreenClass
    c.set(L"MessageId", uo::MakeName(L"BE1v1Prompt")).set<uo::UObject*>(L"WorldContextObject", gi).run();
    p.shownAt = GetTickCount(); p.screen = nullptr; p.labelled = false;
    Log("ui: prompt '%ls'", p.body.c_str());
    return true;
}

// Renames the Yes/No buttons of the prompt screen to our labels.
void LabelPrompt(Prompt& p) {
    uo::UObject* tb = uo::FindClass(L"TextBlock");
    int done = 0;
    for (uo::UObject* w : uo::FindAllTransient(tb)) {
        bool inside = false;
        for (uo::UObject* o = uo::OuterOf(w); o; o = uo::OuterOf(o)) if (o == p.screen) { inside = true; break; }
        if (!inside) continue;
        std::wstring t = GetText(w);
        if (t == L"YES" || t == L"Yes") { SetText(w, p.yes.c_str()); done++; }
        else if (t == L"NO" || t == L"No") { SetText(w, p.no.c_str()); done++; }
    }
    p.labelled = done > 0;
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
    uo::Call par(p.screen, L"GetParent");
    bool open = uo::IsLive(p.screen) && par.ok() && par.run().get<uo::UObject*>(L"ReturnValue");
    if (open) return;
    uint8_t result = uo::IsLive(p.screen) ? F<uint8_t>(p.screen, SMS_MessageResult) : 0;
    Log("ui: prompt closed, result=%d", result);
    auto cb = p.cb;
    gPrompts.erase(gPrompts.begin());
    if (cb) cb(result == 1);
}
}  // namespace

void Ask(const std::wstring& body, const std::wstring& yes, const std::wstring& no, std::function<void(bool)> cb) {
    gPrompts.push_back(Prompt{ body, yes, no, cb, nullptr, 0, false });
}

bool MainMenuReady() {
    uo::UObject* m = uo::FindTransient(uo::FindClass(L"FE_MainMenuScreen_C"));
    uo::UObject* s = uo::FindTransient(uo::FindClass(L"FE_StartScreen_C"));
    auto visible = [](uo::UObject* w) { uo::Call c(w, L"IsVisible"); return c.ok() && c.run().get<bool>(L"ReturnValue"); };
    return m && visible(m) && !(s && visible(s)) && gPrompts.empty();
}

void ShowBusy(bool on) {
    uo::UObject* s = TopScreen();
    if (!s) return;
    if (on) uo::Call(s, L"SetBusyWaiting").set(L"TimeOut", 20.0f).set(L"bClearFocus", true).run();
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
    TickPrompts();
}

void DevCommand(const char* cmd) {
    if (!strcmp(cmd, "ask")) Ask(L"Test prompt body.", L"UPDATE", L"LATER", [](bool y) { Log("ui: dev prompt answered %d", y); });
    if (!strcmp(cmd, "msg")) ShowMessage(L"", L"Test message.");
    if (!strcmp(cmd, "addrow")) settings::DevAddRow();
}

void Install() {
    // Main menu: "Custom Queue" (the dead official password queue) becomes our Custom Game entry.
    OnEvent(L"FE_MainMenuScreen_C", L"OnCustomQueuePressed", [](uo::UObject*, void*) {
        Log("ui: Custom Game pressed");
        if (lobby::Active()) lobby::ShowScreen(); else lobby::CreateAsHost();
        return true;
    });
    OnEvent(L"FE_MainMenuScreen_C", L"OnReportBUgPressed", [](uo::UObject*, void*) {
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
