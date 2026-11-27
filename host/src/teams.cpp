// Custom games with 3 or 4 teams, and the "Knockouts Only" scoring (Team Brawl). The game's simulation already sizes
// its team bookkeeping from the map's NumTeams (rules.cpp writes it), but its objectives are built for two sides: a
// capture point is a tug of war between team 0 and team 1, and a knockout scores for "the team that isn't the
// victim's". With more teams:
// - each capture point runs the game's own capture code with two sides: the team holding it (owner, or whoever has
//   partial progress) and everyone else on it; the result is mapped back to the real teams (see CapUpdate);
// - knockouts score for the attacker's team;
// - the capture point manager's score table (Points) holds one entry per team, and the winner check looks at all;
// - teams 2 and 3 respawn in the bases of teams 0 and 1 (team % 2).
// Everything here runs inside the deterministic rollback simulation on every machine with identical inputs (the
// lobby's rules), except the game-ended result that each player's own screen reads (see EndCheck).
#include <windows.h>
#include <climits>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include "MinHook.h"
#include "uobj.h"
#include "mod.h"

namespace teams {
namespace {
// MBCapturePointManagerState
constexpr size_t CPM_Data = 0x28, CPM_Points = 0x90, CPM_RequiredOverride = 0xb4, CPM_Active = 0x150;
constexpr size_t CPMD_PointsRequiredToWin = 0x4c;
// NTActorState
constexpr size_t AS_TeamId = 0x3bc;
// FMBActorStateInfo-like structs passed to the KO handler (victim / attacker): team at +0x30, valid flag at +0x40
constexpr size_t KO_Team = 0x30, KO_Valid = 0x40;

constexpr uintptr_t A_AddPoints = 0x142a58120;     // void (Mgr*, Ctx*, int TeamId, int Points)
constexpr uintptr_t A_OnPlayerKO = 0x142a58710;    // void (Mgr*, Ctx*, Victim*, Attacker*, Contact*)
constexpr uintptr_t A_EndCheck = 0x142a5bce0;      // void (Mgr*, Ctx*): ends the game when a team reached the target
constexpr uintptr_t A_PickSpawn = 0x1429deaf0;     // bool (CommonLevelObjectState*, Ctx*, PlayerState*, SpawnPoint** Out)
constexpr uintptr_t A_FireEvent = 0x140395190;     // void (EventManager*, Ctx*, int EventId, Args*)
constexpr uintptr_t A_IntArrayGrow = 0x1402f8dd0;  // TArray<int32>::ResizeGrow(Array*, OldNum)
constexpr int Ev_GameEnded = 1;
// MBGameEndedArguments.Params
constexpr size_t GE_LosingTeam = 0x28, GE_Team0Score = 0x2c, GE_Team1Score = 0x30;

int gKoTeam = INT_MIN;         // while a knockout is scored: the team that gets the point (-1: nobody)
struct EndPatch { bool on; int losing, t0, t1; } gEndPatch;
EndPatch gResult;              // this player's view of the last Team Brawl result (for the post-match screens)
void* gResultWorld;

void GrowPoints(uint8_t* mgr, int n) {
    auto& a = F<TArray<int32_t>>(mgr, CPM_Points);
    while (a.Num < n) {
        int old = a.Num;
        a.Num = old + 1;
        if (a.Max < a.Num) Fn<void(__fastcall*)(void*, int)>(A_IntArrayGrow)(&a, old);
        a.Data[old] = 0;
    }
}

using AddPointsFn = void(__fastcall*)(void*, void*, int, int);
AddPointsFn oAddPoints;
struct CapMap { bool on, changed; int real; int side[2]; } gCap;   // during a capture point update (see CapUpdate)
void __fastcall hkAddPoints(void* mgr, void* ctx, int team, int points) {
    if (Active()) {
        GrowPoints((uint8_t*)mgr, Count());
        if (gKoTeam != INT_MIN) {
            if (gKoTeam < 0) return;
            team = gKoTeam;
        }
        else if (gCap.on && !gCap.changed && (team == 0 || team == 1)) team = gCap.side[team];
    }
    oAddPoints(mgr, ctx, team, points);
}

using KoFn = void(__fastcall*)(void*, void*, uint8_t*, uint8_t*, void*);
KoFn oKo;
void __fastcall hkKo(void* mgr, void* ctx, uint8_t* victim, uint8_t* attacker, void* contact) {
    if (!Active() || !victim) { oKo(mgr, ctx, victim, attacker, contact); return; }
    int vt = F<int32_t>(victim, KO_Team);
    int at = attacker && F<uint8_t>(attacker, KO_Valid) ? F<int32_t>(attacker, KO_Team) : -1;
    gKoTeam = at >= 0 && at < Count() && at != vt ? at : -1;
    oKo(mgr, ctx, victim, attacker, contact);
    gKoTeam = INT_MIN;
}

int Threshold(uint8_t* mgr) {
    int t = F<int32_t>(mgr, CPM_RequiredOverride);
    return t > 0 ? t : F<int32_t>(F<uint8_t*>(mgr, CPM_Data), CPMD_PointsRequiredToWin);
}

// The winner check. With two teams it's the game's own (including overtime). With more, the first team to reach the
// target wins (the highest score if several reach it in the same frame, the lower team number on a tie).
// The game reports the result as "the losing team", and every screen compares that with its own player's team. With
// more than two teams there is no single losing team, so each machine reports its own view: its own team when it
// lost, another team when it won. Only the post-match screens read it (the simulation is over at this point).
using EndCheckFn = void(__fastcall*)(void*, void*);
EndCheckFn oEndCheck;
void __fastcall hkEndCheck(void* mgrPtr, void* ctx) {
    if (!Active()) { oEndCheck(mgrPtr, ctx); return; }
    uint8_t* mgr = (uint8_t*)mgrPtr;
    int n = Count();
    GrowPoints(mgr, n);
    auto& pts = F<TArray<int32_t>>(mgr, CPM_Points);
    int thr = Threshold(mgr);
    int winner = -1;
    for (int t = 0; t < n; t++)
        if (pts.Data[t] >= thr && (winner < 0 || pts.Data[t] > pts.Data[winner])) winner = t;
    if (winner < 0) return;
    int me = lobby::MyTeam();
    int best = -1;   // best other team (the one shown as "the enemy" on the result screens)
    for (int t = 0; t < n; t++) if (t != winner && t != me && (best < 0 || pts.Data[t] > pts.Data[best])) best = t;
    int other = me == winner ? best : winner;
    int mine = me >= 0 && me < n ? pts.Data[me] : (best >= 0 ? pts.Data[best] : 0);
    int theirs = other >= 0 ? pts.Data[other] : 0;
    gEndPatch.on = true;
    gEndPatch.losing = me == winner ? (other >= 0 ? other : (me == 0 ? 1 : 0)) : me;
    // Team0Score/Team1Score: the screens show the score of their own team's slot as "ours".
    bool slot0 = me == 0;
    gEndPatch.t0 = std::min(slot0 ? mine : theirs, thr);
    gEndPatch.t1 = std::min(slot0 ? theirs : mine, thr);
    if (!gResult.on || gResultWorld != net::World())
        Log("teams: team %d wins with %d (target %d); this player (team %d) sees %s", winner, pts.Data[winner], thr, me, me == winner ? "victory" : "defeat");
    gResult = gEndPatch; gResultWorld = net::World();
    // Let the game end the match its own way (game-ended event, objectives off) by showing it a two-team table in
    // which "team 0" has reached the target.
    int32_t fake[2] = { thr, 0 };
    int32_t* real = pts.Data;
    pts.Data = fake;
    oEndCheck(mgrPtr, ctx);
    pts.Data = real;
    gEndPatch.on = false;
}

using FireEventFn = void(__fastcall*)(void*, void*, int, uint8_t*);
FireEventFn oFireEvent;
void __fastcall hkFireEvent(void* em, void* ctx, int id, uint8_t* args) {
    if (gEndPatch.on && id == Ev_GameEnded && args) {
        F<int32_t>(args, GE_LosingTeam) = gEndPatch.losing;
        F<int32_t>(args, GE_Team0Score) = gEndPatch.t0;
        F<int32_t>(args, GE_Team1Score) = gEndPatch.t1;
    }

    oFireEvent(em, ctx, id, args);
}

// ---- capture points with 3-4 teams ---------------------------------------------------------------------------
// The game's capture update counts the players on a point as team 0 or team 1 and moves one progress value from
// -1 (team 1) to +1 (team 0). Per point and frame it runs with two sides: side 0 = the team holding the point (its
// owner, or the team whose partial progress it is), side 1 = every other team on it. Players' and the point's team
// ids are swapped for the call and restored after; captures go to the real team (CapturedBy). Afterwards progress is
// stored from the holder's side (positive). While a point is neutral, the holder of its partial progress rides in
// the progress value's lowest bits (2^-22 steps, far below anything visible): it is copied with the frame states,
// so rollback and every machine see the same thing.
constexpr uintptr_t A_CapUpdate = 0x1429de030;     // void UMBCapturePointState::(update)(this, Ctx*)
constexpr uintptr_t A_CapturedBy = 0x1429c34d0;    // void UMBCapturePointState::(set owner)(this, Ctx*, int Team)
constexpr uintptr_t A_CanCapture = 0x1429c2780;    // bool UMBCapturePointState::CanCapture(this, ActorState*)
constexpr size_t CP_Progress = 0x7b4, AS_Touching = 0x780;
uo::UObject* gPlayerClass;
bool IsA(uint8_t* obj, uo::UObject* cls);
float EncodeHolder(float p, int team) {
    float q = floorf(p * 262144.0f) / 262144.0f;
    return q + (float)(team + 1) / 4194304.0f;
}
int DecodeHolder(float p) {
    if (!(p > 0.0f && p < 1.0f)) return -1;
    int r = (int)(p * 4194304.0f - floorf(p * 262144.0f) * 16.0f);
    return r >= 1 && r <= 4 ? r - 1 : -1;
}
using CapUpdateFn = void(__fastcall*)(uint8_t*, void*);
CapUpdateFn oCapUpdate;
void __fastcall hkCapUpdate(uint8_t* pt, void* ctx) {
    if (!Active() || !gPlayerClass) { oCapUpdate(pt, ctx); return; }
    int32_t& team = F<int32_t>(pt, AS_TeamId);
    float& prog = F<float>(pt, CP_Progress);
    int owner = team;
    int holder = owner >= 0 ? owner : prog > 0.0f ? DecodeHolder(prog) : -1;
    // Teams standing on the point (the game's own test).
    bool present[4] = {};
    auto& touch = F<TArray<uint8_t*>>(pt, AS_Touching);
    for (int i = 0; i < touch.Num; i++) {
        uint8_t* a = touch.Data[i];
        if (!a || !IsA(a, gPlayerClass)) continue;
        int t = F<int32_t>(a, AS_TeamId);
        if (t >= 0 && t < 4 && Fn<bool(__fastcall*)(void*, void*)>(A_CanCapture)(pt, a)) present[t] = true;
    }
    if (holder < 0) for (int t = 0; t < 4 && holder < 0; t++) if (present[t]) holder = t;
    int challenger = -1;
    for (int t = 0; t < 4 && challenger < 0; t++) if (present[t] && t != holder) challenger = t;
    // Swap in the two sides.
    struct Moved { uint8_t* a; int32_t t; };
    Moved moved[32]; int nMoved = 0;
    for (int i = 0; i < touch.Num && nMoved < 32; i++) {
        uint8_t* a = touch.Data[i];
        if (!a || !IsA(a, gPlayerClass)) continue;
        int32_t& at = F<int32_t>(a, AS_TeamId);
        if (at < 0) continue;
        moved[nMoved++] = { a, at };
        at = at == holder ? 0 : 1;
    }
    gCap = { true, false, owner, { holder, challenger } };
    team = owner >= 0 ? 0 : -1;
    oCapUpdate(pt, ctx);
    for (int i = nMoved - 1; i >= 0; i--) F<int32_t>(moved[i].a, AS_TeamId) = moved[i].t;
    bool changed = gCap.changed;
    gCap.on = false;
    int mapped = owner >= 0 ? 0 : -1;
    if (!changed) {
        // An owner change outside CapturedBy (the point turns neutral when its progress is pushed back): side ids.
        if (team != mapped) { team = team == 0 ? holder : team == 1 ? challenger : team; changed = true; }
        else team = owner;
    }
    {
        static DWORD lastChange;
        int mask = present[0] | present[1] << 1 | present[2] << 2 | present[3] << 3;
        DWORD now = GetTickCount();
        if (changed && now - lastChange > 1000) {   // rollback replays the same change: once
            lastChange = now;
            Log("teams: capture point %ls: owner %d -> %d (teams on it %x)", uo::Name(pt).c_str(), owner, team, mask);
        }
    }
    // Progress from the holder's side.
    float q = prog;
    if (team >= 0) {
        if (changed && q < 0.0f) q = -q;   // just captured by side 1: the new owner holds it
        prog = q;
    } else {
        int m = q > 0.0f ? holder : q < 0.0f ? challenger : -1;
        if (q < 0.0f) q = -q;
        prog = m >= 0 && q > 0.0f && q < 1.0f ? EncodeHolder(q, m) : q;
    }
}
using CapturedByFn = void(__fastcall*)(uint8_t*, void*, int);
CapturedByFn oCapturedBy;
void __fastcall hkCapturedBy(uint8_t* pt, void* ctx, int side) {
    if (gCap.on) {
        if (side == 0 || side == 1) side = gCap.side[side];
        F<int32_t>(pt, AS_TeamId) = gCap.real;   // the "previous owner" the game reports is the real one
        gCap.changed = true;
    }
    oCapturedBy(pt, ctx, side);
}

// The capture ring's fill for a team (HUD, minimap, the point itself): asked as the holder's side or the other side.
constexpr uintptr_t A_TeamFraction = 0x1429cb170;   // float UMBCapturePointState::GetTeamProgressBarFraction(this, int Team)
using FractionFn = float(__fastcall*)(uint8_t*, int);
FractionFn oFraction;
float __fastcall hkFraction(uint8_t* pt, int team) {
    if (!Active() || gCap.on) return oFraction(pt, team);
    if (team < 0) return 0.0f;
    int32_t& t = F<int32_t>(pt, AS_TeamId);
    float p = F<float>(pt, CP_Progress);
    int owner = t;
    int holder = owner >= 0 ? owner : DecodeHolder(p);
    if (holder < 0 && p == 0.0f) return 0.0f;
    t = owner >= 0 ? 0 : -1;
    float r = oFraction(pt, team == holder ? 0 : 1);
    t = owner;
    return r;
}

// Respawn point choice: teams 2 and 3 use the spawn points of teams 0 and 1.
using PickSpawnFn = bool(__fastcall*)(void*, void*, uint8_t*, void**);
PickSpawnFn oPickSpawn;
bool __fastcall hkPickSpawn(void* clo, void* ctx, uint8_t* ps, void** out) {
    if (!Active() || !ps) return oPickSpawn(clo, ctx, ps, out);
    int32_t& team = F<int32_t>(ps, AS_TeamId);
    int real = team;
    if (real >= 2) team = BaseOf(real);
    bool r = oPickSpawn(clo, ctx, ps, out);
    team = real;
    return r;
}
// "Same team?" for two simulation actors. Each base's objects (the force field at the spawn room's exit, spawn pads,
// the base's protection) belong to team 0 or 1. In shared bases the paired team (team % 2) counts as their owner:
// a team 2 player can leave team 0's spawn room, and is protected there like team 0. Players (and everything they
// own: projectiles, summons) of the two teams stay enemies.
constexpr uintptr_t A_IsSameTeam = 0x142a8dd50;    // bool (NTActorState*, NTActorState*)
constexpr size_t AS_TopLevelOwner = 0x2f0, Class_ChainArray = 0xa8, Class_ChainDepth = 0xb0;
bool IsA(uint8_t* obj, uo::UObject* cls) {
    uint8_t* c = F<uint8_t*>(obj, uo::Obj_Class);
    int d = F<int32_t>(cls, Class_ChainDepth);
    return c && F<int32_t>(c, Class_ChainDepth) >= d && F<uint8_t**>(c, Class_ChainArray)[d] == cls + Class_ChainArray;
}
bool IsMapObject(uint8_t* s) { return F<int64_t>(s, AS_TopLevelOwner) == -1 && !IsA(s, gPlayerClass); }
using SameTeamFn = bool(__fastcall*)(uint8_t*, uint8_t*);
SameTeamFn oSameTeam;
bool __fastcall hkSameTeam(uint8_t* a, uint8_t* b) {
    bool r = oSameTeam(a, b);
    if (r || !a || !b || !gPlayerClass || !Active()) return r;
    int ta = F<int32_t>(a, AS_TeamId), tb = F<int32_t>(b, AS_TeamId);
    if (ta < 0 || tb < 0 || ta == tb || BaseOf(ta) != BaseOf(tb)) return false;
    return IsMapObject(a) || IsMapObject(b);
}
// The match flow (Victory/Defeat splash, result screens) reads the result again from the confirmed frame's copy of
// the game-ended event, which carries the simulation's own two-team answer: it gets this player's view instead.
constexpr uintptr_t A_FlowGameEnded = 0x141050810;   // void UMBGameFlowManager::OnGameEnded(this, int, const FMBGameEndedParams*)
constexpr size_t FM_bGameEndedInDefeat = 0x1bb;
using FlowEndFn = void(__fastcall*)(uint8_t*, int, uint8_t*);
FlowEndFn oFlowEnd;
void __fastcall hkFlowEnd(uint8_t* fm, int a, uint8_t* args) {
    if (!Active() || !gResult.on || gResultWorld != net::World() || !args) { oFlowEnd(fm, a, args); return; }
    int32_t keep[3] = { F<int32_t>(args, GE_LosingTeam), F<int32_t>(args, GE_Team0Score), F<int32_t>(args, GE_Team1Score) };
    F<int32_t>(args, GE_LosingTeam) = gResult.losing;
    F<int32_t>(args, GE_Team0Score) = gResult.t0;
    F<int32_t>(args, GE_Team1Score) = gResult.t1;
    oFlowEnd(fm, a, args);
    F<int32_t>(args, GE_LosingTeam) = keep[0];
    F<int32_t>(args, GE_Team0Score) = keep[1];
    F<int32_t>(args, GE_Team1Score) = keep[2];
    Log("teams: match result shown as %s", F<uint8_t>(fm, FM_bGameEndedInDefeat) ? "defeat" : "victory");
}
// ---- score displays --------------------------------------------------------------------------------------------
// The HUD's score bar (capture point manager widget) and the team score panel show "ally vs enemy" from a two-team
// table. With more teams they show this player's team against the leading other team.
constexpr uintptr_t A_TeamScore = 0x1429cb210;        // int (CommonLevelObjectState*, int TeamId)
constexpr uintptr_t A_AllyEnemyScores = 0x1410124f0;  // void (CLO*, uint8 Mode, int MyTeam, int* Ally, int* Enemy)
constexpr uintptr_t A_CPWidgetTick = 0x141255150;     // void UMBCapturePointManagerWidget::(update)(this)
constexpr uintptr_t A_WidgetTeam = 0x141241e90;       // int UMBBaseWidget::(team of the player it shows)(this)
constexpr size_t CPW_Proxy = 0x3a0, Proxy_State = 0x3b0;
int Leader(const int32_t* pts, int n, int except) {
    int best = -1;
    for (int t = 0; t < n; t++) if (t != except && (best < 0 || pts[t] > pts[best])) best = t;
    return best;
}
using AllyEnemyFn = void(__fastcall*)(void*, uint8_t, int, int32_t*, int32_t*);
AllyEnemyFn oAllyEnemy;
void __fastcall hkAllyEnemy(void* clo, uint8_t mode, int team, int32_t* ally, int32_t* enemy) {
    oAllyEnemy(clo, mode, team, ally, enemy);
    if (!Active() || !clo) return;
    int32_t pts[4] = {};
    int n = Count();
    for (int t = 0; t < n; t++) pts[t] = Fn<int(__fastcall*)(void*, int)>(A_TeamScore)(clo, t);
    int lead = Leader(pts, n, team);
    *ally = team >= 0 && team < n ? pts[team] : (lead >= 0 ? pts[lead] : 0);
    *enemy = lead >= 0 ? pts[lead] : 0;
}
uint8_t* gCPState;                 // the capture point manager state the HUD last showed (latest frame)
using WidgetTickFn = void(__fastcall*)(uint8_t*);
WidgetTickFn oCPWidgetTick;
void __fastcall hkCPWidgetTick(uint8_t* w) {
    uint8_t* proxy = Active() ? F<uint8_t*>(w, CPW_Proxy) : nullptr;
    uint8_t* st = proxy ? F<uint8_t*>(proxy, Proxy_State) : nullptr;
    auto* pts = st ? &F<TArray<int32_t>>(st, CPM_Points) : nullptr;
    if (!pts || pts->Num < 2 || !pts->Data) { oCPWidgetTick(w); return; }
    gCPState = st;
    int n = std::min(pts->Num, Count());
    int team = Fn<int(__fastcall*)(void*)>(A_WidgetTeam)(w);
    int lead = Leader(pts->Data, n, team);
    int mine = team >= 0 && team < n ? pts->Data[team] : 0, theirs = lead >= 0 ? pts->Data[lead] : 0;
    int allySlot = (unsigned)(team + 1) < 2 ? 0 : 1;   // the widget's own rule: team -1/0 -> slot 0, else slot 1
    int32_t view[2];
    view[allySlot] = mine; view[1 - allySlot] = theirs;
    TArray<int32_t> real = *pts;
    pts->Data = view; pts->Num = 2;
    oCPWidgetTick(w);
    *pts = real;
}

// ---- the team score row ----------------------------------------------------------------------------------------
// Under the score bar the HUD has a line for the objectives' timer ("OBJECTIVES ACTIVATING IN"), which Team Brawl
// doesn't use. It is replaced by every team's score in its colour; the objective icons are hidden.
constexpr uintptr_t A_StaticConstructObject = 0x1416aac50;
const wchar_t* kTeamNames[] = { L"BLUE", L"RED", L"YELLOW", L"GREEN" };
uo::UObject* NewWidget(const wchar_t* cls, uo::UObject* outer, const wchar_t* name, uo::UObject* tmpl) {
    uo::UObject* c = uo::FindClass(cls);
    if (!c || !outer) return nullptr;
    using SCO = uo::UObject*(__fastcall*)(uo::UObject*, uo::UObject*, FName, uint32_t, uint32_t, uo::UObject*, bool, void*, bool);
    return Fn<SCO>(A_StaticConstructObject)(c, outer, uo::MakeName(name), 0, 0, tmpl, false, nullptr, false);
}
uo::UObject* Prop(uo::UObject* w, const wchar_t* name) {
    int off = uo::PropOffset(uo::ClassOf(w), name);
    return off >= 0 ? F<uo::UObject*>(w, off) : nullptr;
}
void SetVis(uo::UObject* w, uint8_t v) {
    if (!w) return;
    uo::Call g(w, L"GetVisibility");
    if (g.ok() && g.run().get<uint8_t>(L"ReturnValue") != v) uo::Call(w, L"SetVisibility").set<uint8_t>(L"InVisibility", v).run();
}
void SetText(uo::UObject* tb, const std::wstring& text) {
    static int off = -2;
    if (off == -2) off = uo::PropOffset(uo::FindClass(L"TextBlock"), L"Text");
    if (!tb || off < 0 || ui::TextToString(tb + off) == text) return;
    uo::FText t; uo::MakeText(&t, text.c_str());
    uo::Call(tb, L"SetText").set(L"InText", t).run();
}
void SetColour(uo::UObject* tb, const float* rgb) {
    uo::Call c(tb, L"SetColorAndOpacity");
    int o = c.off(L"InColorAndOpacity");
    if (!c.ok() || o < 0) return;
    float col[4] = { rgb[0], rgb[1], rgb[2], 1.0f };
    memcpy(c.buf.data() + o, col, 16);   // FSlateColor: SpecifiedColor, then ColorUseRule 0 (specified)
    c.run();
}
struct ScoreRow { uo::UObject* hud = nullptr; uo::UObject* box = nullptr; uo::UObject* text[4] = {}; } gRow;
void ScoreRowTick() {
    static DWORD last;
    DWORD now = GetTickCount();
    if (now - last < 250) return;
    last = now;
    uo::UObject* hud = nullptr;
    for (uo::UObject* w : uo::FindAllTransient(uo::FindClass(L"Widget_PointsManager_C"))) {
        uo::Call p(w, L"GetParent");
        if (p.ok() && p.run().get<uo::UObject*>(L"ReturnValue")) { hud = w; break; }
    }
    if (!hud) return;
    uo::UObject* timerLine = Prop(hud, L"ActiveTimerTextContainer");
    uo::UObject* label = Prop(hud, L"CapturePointsActiveText");
    if (KoOnly()) {   // no objectives: their timer line and icons go
        SetVis(timerLine, 1);
        SetVis(Prop(hud, L"CPTimerBorder"), 1);
        for (uo::UObject* icon : { Prop(hud, L"Widget_CapturePoint"), Prop(hud, L"Widget_CapturePoint_6"), Prop(hud, L"Widget_CapturePoint_7") }) SetVis(icon, 1);
    }
    if (!Active()) return;   // the row of every team's score: 3-4 teams
    if (gRow.hud != hud || !gRow.box || !uo::IsLive(gRow.box)) {
        gRow = ScoreRow{};
        uo::Call p(Prop(hud, L"ActiveTimerBorder"), L"GetParent");
        uo::UObject* column = p.ok() ? p.run().get<uo::UObject*>(L"ReturnValue") : nullptr;   // VerticalBox_0
        if (!column || !label) return;
        uo::UObject* tree = uo::OuterOf(label);
        uo::UObject* box = NewWidget(L"HorizontalBox", tree, L"TeamBrawlScores", nullptr);
        if (!box) return;
        uo::UObject* slot = uo::Call(column, L"AddChild").set<uo::UObject*>(L"Content", box).run().get<uo::UObject*>(L"ReturnValue");
        if (slot) uo::Call(slot, L"SetHorizontalAlignment").set<uint8_t>(L"InHorizontalAlignment", 2).run();   // centre
        for (int t = 0; t < Count(); t++) {
            uo::UObject* tb = NewWidget(L"TextBlock", tree, (std::wstring(L"TeamBrawlScore") + std::to_wstring(t)).c_str(), label);
            if (!tb) continue;
            uo::UObject* s2 = uo::Call(box, L"AddChild").set<uo::UObject*>(L"Content", tb).run().get<uo::UObject*>(L"ReturnValue");
            if (s2) {
                uo::Call c(s2, L"SetPadding");
                int o = c.off(L"InPadding");
                float pad[4] = { 10, 2, 10, 0 };
                if (o >= 0) { memcpy(c.buf.data() + o, pad, 16); c.run(); }
            }
            SetVis(tb, 3);   // HitTestInvisible
            SetColour(tb, Colour(t));
            gRow.text[t] = tb;
        }
        gRow.hud = hud; gRow.box = box;
        Log("teams: score row added (%d teams)", Count());
    }
    int me = lobby::MyTeam();
    auto* pts = gCPState && uo::IsLive(gCPState) ? &F<TArray<int32_t>>(gCPState, CPM_Points) : nullptr;
    for (int t = 0; t < Count(); t++) {
        int v = pts && pts->Data && t < pts->Num ? pts->Data[t] : 0;
        std::wstring s = std::wstring(kTeamNames[t]) + L" " + std::to_wstring(v) + (t == me ? L" (YOU)" : L"");
        SetText(gRow.text[t], s);
    }
}
// "Objective Control" texts of the screens that name the mode (loading screen, fighter select) and the loading
// screen's tips read "Team Brawl" and its rules.
void RelabelLoadingScreen(uo::UObject* w) {
    if (!w || !uo::IsLive(w)) return;
    SetText(Prop(w, L"GameModeText"), L"Team Brawl");
    // Tip bubbles: their two text lines (the bubble's own update function crashed the loading screen, which another
    // thread draws while the map loads).
    struct Tip { const wchar_t* name; const wchar_t* text; };
    static const Tip tips[] = { { L"TextBubble1", L"Knock out enemies to score points & win!" },
                                { L"TextBubble2", L"Every knockout scores for your team" } };
    for (auto& tip : tips)
        if (uo::UObject* b = Prop(w, tip.name))
            for (const wchar_t* line : { L"TextBlock_0", L"TextBlock_1Captureobjec" }) SetText(Prop(b, line), tip.text);
}
// Fighter select's match info panel (FE_MatchCountdown_C) names the mode in its "GameMode" text.
void RelabelMatchInfo(uo::UObject* panel) {
    static FName gameMode = uo::MakeName(L"GameMode");
    for (uo::UObject* tb : uo::FindAll(uo::FindClass(L"TextBlock")))
        if (uo::NameIs(tb, gameMode) && !uo::IsDefault(tb) && uo::OuterOf(tb) && (!panel || uo::OuterOf(uo::OuterOf(tb)) == panel)) {
            uo::Call p(tb, L"GetParent");
            if (p.ok() && p.run().get<uo::UObject*>(L"ReturnValue")) SetText(tb, L"Team Brawl");
        }
}
void RelabelNow() {
    for (uo::UObject* w : uo::FindAll(uo::FindClass(L"Widget_LoadingScreen_CP_C"))) if (!uo::IsDefault(w)) RelabelLoadingScreen(w);
    RelabelMatchInfo(nullptr);
}

// ---- shared spawn rooms -----------------------------------------------------------------------------------------
// Two teams share each base (team % 2). A player inside a shared spawn room is invisible to the other team of that
// base, and visible again once outside, where they can be fought. The room is the area around the base's spawn
// pads (from the simulation's spawn point states). Only this player's screen changes (actor visibility), never the
// simulation.
constexpr size_t AS_Location = 0x2c0;        // NTActorState WorldTransform translation (x, y, z floats)
constexpr size_t Proxy_TeamId = 0x438;       // MBProxyActor::LastFrameTeamId
struct Zone { float x0 = 1e9f, y0 = 1e9f, z0 = 1e9f, x1 = -1e9f, y1 = -1e9f, z1 = -1e9f; bool ok = false; } gZone[2];
void* gZoneWorld;
std::vector<uo::UObject*> gHidden;           // pawns we made invisible
void BuildZones() {
    gZone[0] = gZone[1] = Zone{};
    for (uo::UObject* sp : uo::FindAll(uo::FindClass(L"MBSpawnPointState"))) {
        int t = F<int32_t>(sp, AS_TeamId);
        if (t < 0 || t > 1) continue;
        const float* p = (const float*)(sp + AS_Location);
        Zone& z = gZone[t];
        z.x0 = std::min(z.x0, p[0]); z.y0 = std::min(z.y0, p[1]); z.z0 = std::min(z.z0, p[2]);
        z.x1 = std::max(z.x1, p[0]); z.y1 = std::max(z.y1, p[1]); z.z1 = std::max(z.z1, p[2]);
        z.ok = true;
    }
    for (Zone& z : gZone) if (z.ok) { z.x0 -= 550; z.y0 -= 550; z.x1 += 550; z.y1 += 550; z.z0 -= 400; z.z1 += 700; }
    if (gZone[0].ok && gZone[1].ok)
        Log("teams: spawn rooms %.0f..%.0f x %.0f..%.0f and %.0f..%.0f x %.0f..%.0f", gZone[0].x0, gZone[0].x1, gZone[0].y0, gZone[0].y1,
            gZone[1].x0, gZone[1].x1, gZone[1].y0, gZone[1].y1);
}
bool InZone(const Zone& z, const float* p) { return z.ok && p[0] >= z.x0 && p[0] <= z.x1 && p[1] >= z.y0 && p[1] <= z.y1 && p[2] >= z.z0 && p[2] <= z.z1; }
void SetHidden(uo::UObject* pawn, bool hide) {
    auto it = std::find(gHidden.begin(), gHidden.end(), pawn);
    if (hide == (it != gHidden.end())) return;
    uo::Call(pawn, L"SetActorHiddenInGame").set<bool>(L"bNewHidden", hide).run();
    if (hide) gHidden.push_back(pawn); else gHidden.erase(it);
}
void SpawnGhostTick() {
    static DWORD last;
    DWORD now = GetTickCount();
    if (now - last < 100) return;
    last = now;
    void* world = net::World();
    if (world != gZoneWorld) { gZoneWorld = world; gHidden.clear(); gZone[0].ok = gZone[1].ok = false; }
    static DWORD lastBuild;
    if ((!gZone[0].ok || !gZone[1].ok) && now - lastBuild > 2000) { lastBuild = now; BuildZones(); }
    int me = lobby::MyTeam();
    for (auto it = gHidden.begin(); it != gHidden.end();) it = uo::IsLive(*it) ? it + 1 : gHidden.erase(it);
    for (uo::UObject* pawn : uo::FindAll(uo::FindClass(L"MBProxyPawn"))) {
        if (uo::IsDefault(pawn)) continue;
        int t = F<int32_t>(pawn, Proxy_TeamId);
        bool hide = false;
        if (me >= 0 && t >= 0 && t != me && BaseOf(t) == BaseOf(me)) {
            uo::Call loc(pawn, L"K2_GetActorLocation");
            if (loc.ok()) {
                loc.run();
                int o = loc.off(L"ReturnValue");
                hide = o >= 0 && InZone(gZone[BaseOf(t)], (const float*)(loc.buf.data() + o));
            }
        }
        SetHidden(pawn, hide);
    }
}

// ---- team colours in the world -----------------------------------------------------------------------------------
// The game draws allies blue and every enemy red. Enemies of the extra teams get their team's colour on their
// floating name and health bar (yellow / green); teams 1 and 2 keep the game's look.
constexpr size_t BW_OwnerActor = 0x308;      // UMBBaseWidget::WidgetOwnerActor
void BarColourTick() {
    static DWORD last;
    DWORD now = GetTickCount();
    if (now - last < 250) return;
    last = now;
    uo::UObject* cls = uo::FindClass(L"Widget_FloatingHealthBar_C");
    static int enemyOff = -2;
    if (cls && enemyOff == -2) enemyOff = uo::PropOffset(cls, L"EnemyColor");
    if (!cls || enemyOff < 0) return;
    int me = lobby::MyTeam();
    for (uo::UObject* bar : uo::FindAllTransient(cls)) {
        uo::UObject* owner = F<uo::UObject*>(bar, BW_OwnerActor);
        if (!owner || !uo::IsLive(owner)) continue;
        int t = F<int32_t>(owner, Proxy_TeamId);
        if (t < 2 || t > 3 || t == me) continue;
        float* c = (float*)(bar + enemyOff);
        const float* tc = Colour(t);
        if (c[0] != tc[0] || c[1] != tc[1] || c[2] != tc[2]) { c[0] = tc[0]; c[1] = tc[1]; c[2] = tc[2]; c[3] = 1.0f; }
    }
}
}  // namespace

void Tick() {
    if (!gPlayerClass) gPlayerClass = uo::FindClass(L"MBPlayerState");
    if ((Active() || KoOnly()) && net::InNetGame() && !net::InFrontend()) {
        ui::ResolveInMatch();
        ScoreRowTick();
        SpawnGhostTick();
        BarColourTick();
        static DWORD last;
        if (GetTickCount() - last > 1000) { last = GetTickCount(); RelabelNow(); }
    }
}
void Relabel(uint8_t* loadingScreen) { if (KoOnly()) { RelabelLoadingScreen(loadingScreen); RelabelNow(); } }

bool Active() { return lobby::Active() && rules::Current().teams > 2; }
bool KoOnly() { return lobby::Active() && rules::Current().koOnly != 0; }
int Count() { return lobby::Active() ? std::max(2, std::min(4, rules::Current().teams)) : 2; }
int BaseOf(int team) { return team < 0 ? team : team % 2; }
const float* Colour(int team) {
    // Blue and red as the game's lobby draws them; yellow and green in the same strength.
    static const float c[5][3] = { { 0.067f, 0.631f, 0.875f }, { 0.824f, 0.039f, 0.055f }, { 0.98f, 0.70f, 0.04f }, { 0.18f, 0.74f, 0.13f }, { 0.5f, 0.5f, 0.5f } };
    return c[team >= 0 && team < 4 ? team : 4];
}

void Install() {
    MH_CreateHook((void*)VA(A_AddPoints), (void*)&hkAddPoints, (void**)&oAddPoints);
    MH_CreateHook((void*)VA(A_OnPlayerKO), (void*)&hkKo, (void**)&oKo);
    MH_CreateHook((void*)VA(A_EndCheck), (void*)&hkEndCheck, (void**)&oEndCheck);
    MH_CreateHook((void*)VA(A_FireEvent), (void*)&hkFireEvent, (void**)&oFireEvent);
    MH_CreateHook((void*)VA(A_PickSpawn), (void*)&hkPickSpawn, (void**)&oPickSpawn);
    MH_CreateHook((void*)VA(A_CapUpdate), (void*)&hkCapUpdate, (void**)&oCapUpdate);
    MH_CreateHook((void*)VA(A_CapturedBy), (void*)&hkCapturedBy, (void**)&oCapturedBy);
    MH_CreateHook((void*)VA(A_TeamFraction), (void*)&hkFraction, (void**)&oFraction);
    MH_CreateHook((void*)VA(A_IsSameTeam), (void*)&hkSameTeam, (void**)&oSameTeam);
    MH_CreateHook((void*)VA(A_FlowGameEnded), (void*)&hkFlowEnd, (void**)&oFlowEnd);
    MH_CreateHook((void*)VA(A_AllyEnemyScores), (void*)&hkAllyEnemy, (void**)&oAllyEnemy);
    MH_CreateHook((void*)VA(A_CPWidgetTick), (void*)&hkCPWidgetTick, (void**)&oCPWidgetTick);
    // Mode name on fighter select (its countdown panel writes it in ShowGameMode) and on the loading screen
    // (written when it is built, before the map loads).
    ui::OnEventAfter(L"FE_MatchCountdown_C", L"ShowGameMode", [](uint8_t* self, void*, uint8_t*) { if (KoOnly()) RelabelMatchInfo(self); });
    for (const wchar_t* ev : { L"Construct", L"OnLoadBegin", L"OnLoadingScreenRuntimeDataChanged" })
        ui::OnEventAfter(L"Widget_LoadingScreen_CP_C", ev, [](uint8_t* self, void*, uint8_t*) { if (KoOnly()) RelabelLoadingScreen(self); });
    Log("teams: hooks created");
}
}  // namespace teams
