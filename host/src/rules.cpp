// Match rules for custom games. The host picks them in the Custom Game settings panel; they travel in the lobby data
// and every player applies the same values to the map's objective data while the match world loads (before the
// match starts), so the deterministic rollback simulation stays identical on all machines.
#include <windows.h>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <cwctype>
#include <cwchar>
#include "MinHook.h"
#include "uobj.h"
#include "mod.h"

namespace rules {
namespace {
// Map modifiers (ids from the game's map mod list) and their names in the settings panel.
const wchar_t* kModIds[] = { L"DoubleDamage", L"SuperPowered", L"Killstreak", L"ExplodeOnDeath", L"CellPowerup", L"AllObjectives",
                             L"Barriers", L"PowerZones", L"SingleObjective", L"Slime", L"SpeedPads", L"VIP" };
const wchar_t* kModNames[] = { L"Double Damage", L"Super Powered", L"Killstreaks", L"Explode on Death", L"Cell Powerups",
                               L"All Objectives", L"Barriers", L"Power Zones", L"Single Objective", L"Slime", L"Speed Pads", L"VIP" };
constexpr int kNumMods = sizeof(kModIds) / sizeof(kModIds[0]);
constexpr uintptr_t A_ActiveModsCVarValue = 0x145341278;   // FString* of the MapMods.ActiveMapMods console variable
constexpr uintptr_t A_ModsFromCVar = 0x14102c6b0;          // bool UMBMapModsManager::TrySetActiveMapModsFromCVar()
constexpr uintptr_t A_ModsWorldInit = 0x14101a6d0;         // UMBMapModsManager world init (reads the CVar offline only)
const wchar_t* kObjText[] = { L"Default", L"Rotate Faster", L"Rotate Slower", L"Never Rotate" };   // objective rotation
const float kObjMul[] = { 1.0f, 0.5f, 2.0f, 0.0f };
const wchar_t* kCapText[] = { L"Default", L"Fast", L"Slow" };                // capture speed
const float kCapMul[] = { 1.0f, 0.5f, 2.0f };
const wchar_t* kTeamText[] = { L"1v1", L"2v2", L"3v3", L"4v4" };
const wchar_t* kModModeText[] = { L"Off", L"Choose", L"All" };

Values gCur;                       // current rules (host: from the panel; members: from the lobby)

// MBCapturePointManagerData / MBCapturePointData / MBSeedManagerActorData fields
constexpr size_t PMD_PointsRequiredToWin = 0x4c, PMD_InfiniteCycle = 0x98, PMD_CycleActiveTime = 0x9c;
// Scoring sources (Team Brawl: knockouts only) and the delay before the first objectives open
constexpr size_t PMD_PointsOnKO = 0x30, PMD_PointsOnPortal = 0x34, PMD_PointsOnTick = 0x38, PMD_PointsOnCapture = 0x3c,
                 PMD_CycleWaitInitial = 0x94;
constexpr size_t CPD_CaptureTime = 0x220;
constexpr size_t SMD_SeedsRequiredValue = 0x1b0;   // SeedsRequired (struct at 0x188) base value: 50 on every map

// Score choices: index 0 keeps the map's own target.
std::vector<int> MakeSteps(std::initializer_list<std::pair<int, int>> ranges /* (to, step) */, int from) {
    std::vector<int> v = { 0 };
    int x = from;
    for (auto& r : ranges) for (; x <= r.first; x += r.second) v.push_back(x);
    return v;
}
const std::vector<int>& CpValues() { static std::vector<int> v = MakeSteps({ { 1000, 50 }, { 2000, 100 }, { 5000, 500 } }, 50); return v; }
const std::vector<int>& PcValues() { static std::vector<int> v = MakeSteps({ { 30, 1 }, { 100, 5 }, { 200, 10 } }, 1); return v; }
std::vector<std::wstring> Texts(const std::vector<int>& v) {
    std::vector<std::wstring> t;
    for (int x : v) t.push_back(x ? std::to_wstring(x) : L"Default");
    return t;
}
int IndexOf(const std::vector<int>& v, int x) { for (size_t i = 0; i < v.size(); i++) if (v[i] == x) return (int)i; return 0; }
}  // namespace

int NumMods() { return kNumMods; }
// Display names come from the game's map mod list (the names its HUD shows); the table above is the fallback.
const wchar_t* ModName(int i) {
    static std::wstring names[kNumMods];
    static bool loaded;
    if (i < 0 || i >= kNumMods) return L"";
    if (!loaded) {
        uo::UObject* mgr = uo::FindFirst(uo::FindClass(L"MBMapModsManager"));
        uo::UObject* st = uo::FindObjectPath(L"/Script/Moblade.MBMapModInfo");
        if (mgr && st) {
            loaded = true;
            int32_t size = F<int32_t>(st, uo::Struct_Size);
            auto& list = F<TArray<uint8_t>>(mgr, 0x40);
            for (int k = 0; k < list.Num; k++) {
                uint8_t* e = list.Data + (size_t)k * size;
                std::wstring id = uo::NameStr(F<FName>(e, 0));
                for (int j = 0; j < kNumMods; j++)
                    if (id == kModIds[j]) {
                        std::wstring n = ui::TextToString(e + 0x28);
                        if (!n.empty()) {   // "KING OF THE HILL" -> "King of the Hill"
                            bool start = true;
                            for (auto& c : n) { c = start ? towupper(c) : towlower(c); start = c == L' ' || c == L'-'; }
                            for (const wchar_t* w : { L" Of ", L" The ", L" On " }) {
                                size_t p = n.find(w);
                                if (p != std::wstring::npos) for (size_t q = p + 1; q < p + wcslen(w) - 1; q++) n[q] = towlower(n[q]);
                            }
                            if (n == L"Vip") n = L"VIP";
                            names[j] = n;
                        }
                    }
            }
        }
    }
    return names[i].empty() ? kModNames[i] : names[i].c_str();
}

// Sets the MapMods.ActiveMapMods console variable to the lobby's modifiers ("" outside custom games).
std::wstring ModList(uint32_t mods) {
    std::wstring r;
    for (int i = 0; i < kNumMods; i++) if (mods & (1u << i)) { if (!r.empty()) r += L","; r += kModIds[i]; }
    return r;
}
void SetModsCVar(const std::wstring& v) {
    FString* s = *(FString**)VA(A_ActiveModsCVarValue);
    if (s) uo::SetFString(*s, v);
}

// Writes the rules into the map's objective data. Every value is computed from the map's original value (kept per
// object), so applying twice is harmless.
namespace {
std::map<uo::UObject*, std::pair<int, float>> gOrigPoints;   // points manager data -> (PointsRequiredToWin, CycleActiveTime)
std::map<uo::UObject*, std::pair<bool, bool>> gOrigCycle;    // -> InfiniteCycle as designed
struct Scoring { int ko, portal, tick, capture; float wait; };
std::map<uo::UObject*, Scoring> gOrigScoring;                  // -> scoring sources as designed
std::map<uo::UObject*, float> gOrigCapture;                    // capture point data -> CaptureTime
std::map<uo::UObject*, int> gOrigSeeds;                        // seed manager data -> SeedsRequired
std::map<uo::UObject*, int> gOrigNumTeams;                     // common level object data -> NumTeams
constexpr size_t CLD_NumTeams = 0x30;
int ApplyTo(const std::vector<uo::UObject*>& points, const std::vector<uo::UObject*>& caps, const std::vector<uo::UObject*>& seeds,
            const std::vector<uo::UObject*>& levels, bool log) {
    int n = 0;
    for (uo::UObject* d : levels) {
        if (!gOrigNumTeams.count(d)) gOrigNumTeams[d] = F<int32_t>(d, CLD_NumTeams);
        int orig = gOrigNumTeams[d];
        if (orig < 1 || orig > 8) continue;
        F<int32_t>(d, CLD_NumTeams) = gCur.teams > 2 ? gCur.teams : orig;
        if (log) Log("rules: %ls teams %d -> %d", uo::Name(d).c_str(), orig, F<int32_t>(d, CLD_NumTeams));
        n++;
    }
    for (uo::UObject* d : points) {
        if (!gOrigPoints.count(d)) { gOrigPoints[d] = { F<int32_t>(d, PMD_PointsRequiredToWin), F<float>(d, PMD_CycleActiveTime) }; gOrigCycle[d] = { F<bool>(d, PMD_InfiniteCycle), true }; }
        auto o = gOrigPoints[d];
        if (!gOrigScoring.count(d))
            gOrigScoring[d] = { F<int32_t>(d, PMD_PointsOnKO), F<int32_t>(d, PMD_PointsOnPortal), F<int32_t>(d, PMD_PointsOnTick),
                                F<int32_t>(d, PMD_PointsOnCapture), F<float>(d, PMD_CycleWaitInitial) };
        Scoring sc = gOrigScoring[d];
        bool brawl = gCur.koOnly != 0;
        // Team Brawl: one point per knockout, first to the target wins; the objectives never open.
        F<int32_t>(d, PMD_PointsRequiredToWin) = brawl ? KoTarget(gCur) : gCur.cp > 0 ? gCur.cp : o.first;
        F<int32_t>(d, PMD_PointsOnKO) = brawl ? 1 : sc.ko;
        F<int32_t>(d, PMD_PointsOnPortal) = brawl ? 0 : sc.portal;
        F<int32_t>(d, PMD_PointsOnTick) = brawl ? 0 : sc.tick;
        F<int32_t>(d, PMD_PointsOnCapture) = brawl ? 0 : sc.capture;
        F<float>(d, PMD_CycleWaitInitial) = brawl ? 1.0e8f : sc.wait;
        float mul = kObjMul[gCur.objectives];
        F<bool>(d, PMD_InfiniteCycle) = mul == 0.0f ? true : gOrigCycle[d].first;
        F<float>(d, PMD_CycleActiveTime) = mul == 0.0f ? o.second : o.second * mul;
        if (log) Log("rules: %ls points %d -> %d, rotation %.0f s -> %s%.0f s", uo::Name(d).c_str(), o.first, F<int32_t>(d, PMD_PointsRequiredToWin),
                     o.second, F<bool>(d, PMD_InfiniteCycle) ? "never, " : "", F<float>(d, PMD_CycleActiveTime));
        n++;
    }
    for (uo::UObject* d : caps) {
        if (!gOrigCapture.count(d)) gOrigCapture[d] = F<float>(d, CPD_CaptureTime);
        F<float>(d, CPD_CaptureTime) = gOrigCapture[d] * kCapMul[gCur.capture];
        n++;
    }
    for (uo::UObject* d : seeds) {
        if (!gOrigSeeds.count(d)) gOrigSeeds[d] = F<int32_t>(d, SMD_SeedsRequiredValue);
        int orig = gOrigSeeds[d];
        if (orig <= 0 || orig > 100000) continue;   // not the layout we know
        F<int32_t>(d, SMD_SeedsRequiredValue) = gCur.pc > 0 ? gCur.pc : orig;
        if (log) Log("rules: %ls cells %d -> %d", uo::Name(d).c_str(), orig, F<int32_t>(d, SMD_SeedsRequiredValue));
        n++;
    }
    return n;
}
void ApplyNow(bool fullScan, bool log) {
    auto find = [&](const wchar_t* c) { uo::UObject* cls = uo::FindClass(c); return fullScan ? uo::FindAllNow(cls) : uo::FindAll(cls); };
    ApplyTo(find(L"MBCapturePointManagerData"), find(L"MBCapturePointData"), find(L"MBSeedManagerActorData"), find(L"MBCommonLevelObjectActorData"), log);
}
}  // namespace

// The map mods manager reads the console variable only in offline play; custom games read it on every machine,
// so host and members run the same modifiers in the deterministic simulation. The same moment (the match world is
// loaded, nothing simulated yet) is when the objective rules are written.
using WorldInitFn = void(__fastcall*)(void*, void*);
WorldInitFn oModsWorldInit;
void __fastcall hkModsWorldInit(void* mgr, void* worldRef) {
    if (lobby::Active() && gCur.mods) {
        std::wstring list = ModList(gCur.mods);
        SetModsCVar(list);
        bool ok = Fn<bool(__fastcall*)(void*)>(A_ModsFromCVar)(mgr);
        Log("rules: map mods '%ls' -> %d", list.c_str(), ok);
    } else SetModsCVar(L"");
    if (lobby::Active()) {
        gOrigPoints.clear(); gOrigCycle.clear(); gOrigCapture.clear(); gOrigSeeds.clear(); gOrigNumTeams.clear(); gOrigScoring.clear();
        ApplyNow(true, true);
    }
    oModsWorldInit(mgr, worldRef);
}
void Install() {
    MH_CreateHook((void*)VA(A_ModsWorldInit), (void*)&hkModsWorldInit, (void**)&oModsWorldInit);
}

const wchar_t* const* ObjectiveOptions(int* n) { *n = 4; return kObjText; }
const wchar_t* const* CaptureOptions(int* n) { *n = 3; return kCapText; }
const wchar_t* const* TeamSizeOptions(int* n) { *n = 4; return kTeamText; }
// "2v2v2" style labels for a number of teams
std::vector<std::wstring> TeamSizeLabels(int teams) {
    std::vector<std::wstring> v;
    for (int size = 1; size <= 4; size++) {
        std::wstring s = std::to_wstring(size);
        for (int t = 1; t < teams; t++) s += L"v" + std::to_wstring(size);
        v.push_back(s);
    }
    return v;
}
std::vector<std::wstring> TeamCountOptions() { return { L"2 Teams", L"3 Teams", L"4 Teams" }; }
const std::vector<int>& KoValues() { static std::vector<int> v = MakeSteps({ { 50, 5 }, { 100, 10 } }, 5); return v; }
std::vector<std::wstring> KoOptions() { return Texts(KoValues()); }
std::vector<std::wstring> ScoringOptions() { return { L"Objectives", L"Knockouts Only" }; }
int KoIndex(int value) { return IndexOf(KoValues(), value); }
int KoValueAt(int i) { return i >= 0 && i < (int)KoValues().size() ? KoValues()[i] : 0; }
const wchar_t* const* ModModeOptions(int* n) { *n = 3; return kModModeText; }
std::vector<std::wstring> CpScoreOptions() { return Texts(CpValues()); }
std::vector<std::wstring> PcScoreOptions() { return Texts(PcValues()); }
int CpIndex(int value) { return IndexOf(CpValues(), value); }
int PcIndex(int value) { return IndexOf(PcValues(), value); }
int CpValueAt(int i) { return i >= 0 && i < (int)CpValues().size() ? CpValues()[i] : 0; }
int PcValueAt(int i) { return i >= 0 && i < (int)PcValues().size() ? PcValues()[i] : 0; }

Values Current() { return gCur; }
// Knockouts to win a Team Brawl: the host's choice, else 5 per player on a team plus 5 (1v1v1: 10, 4v4v4v4: 25).
int KoTarget(const Values& v) { return v.kos > 0 ? v.kos : 5 * std::max(1, v.teamSize) + 5; }
void Set(const Values& v) {
    if (v.cp != gCur.cp || v.pc != gCur.pc || v.objectives != gCur.objectives || v.capture != gCur.capture || v.teamSize != gCur.teamSize || v.mods != gCur.mods || v.teams != gCur.teams || v.kos != gCur.kos || v.koOnly != gCur.koOnly)
        Log("rules: points=%d cells=%d rotation=%d capture=%d team=%d mods=%x teams=%d", v.cp, v.pc, v.objectives, v.capture, v.teamSize, v.mods, v.teams);
    gCur = v;
}
std::string Encode() {
    char b[96]; snprintf(b, sizeof b, "%d,%d,%d,%d,%u,%d,%d,%d,%d,%d", gCur.cp, gCur.objectives, gCur.capture, gCur.teamSize, gCur.mods, gCur.pc, gCur.modMode, gCur.teams, gCur.kos, gCur.koOnly);
    return b;
}
Values Decode(const std::string& s) {
    Values v;
    if (!s.empty()) sscanf(s.c_str(), "%d,%d,%d,%d,%u,%d,%d,%d,%d,%d", &v.cp, &v.objectives, &v.capture, &v.teamSize, &v.mods, &v.pc, &v.modMode, &v.teams, &v.kos, &v.koOnly);
    if (v.cp < 0 || v.cp > 100000) v.cp = 0;
    if (v.pc < 0 || v.pc > 10000) v.pc = 0;
    v.mods &= (1u << kNumMods) - 1;
    if (v.objectives < 0 || v.objectives > 3) v.objectives = 0;
    if (v.capture < 0 || v.capture > 2) v.capture = 0;
    if (v.teamSize < 1 || v.teamSize > 4) v.teamSize = 4;
    if (v.modMode < 0 || v.modMode > 2) v.modMode = v.mods ? 1 : 0;
    if (v.teams < 2 || v.teams > 4) v.teams = 2;
    if (v.kos < 0 || v.kos > 1000) v.kos = 0;
    v.koOnly = v.koOnly ? 1 : 0;
    return v;
}

// Safety net: the rules are written at world init; this re-applies them while the match world streams in (objective
// data in streamed sub-levels appears later). Keyed by world, so a second match on the same map is covered too.
void Tick() {
    static void* world; static int passes; static DWORD last;
    if (!lobby::Active() || !net::InNetGame()) { world = nullptr; return; }
    DWORD now = GetTickCount();
    if (now - last < 500) return;
    last = now;
    void* w = net::World();
    if (w != world) {
        world = w; passes = 0;
        uo::Prewarm({ L"MBCapturePointManagerData", L"MBCapturePointData", L"MBSeedManagerActorData", L"MBCommonLevelObjectActorData" });   // one pass for all three
    }
    if (passes > 20) return;
    passes++;
    ApplyNow(false, passes == 1 || passes == 20);
}

void ApplyOnMapLoad() {}
}  // namespace rules
