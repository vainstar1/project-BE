// Match rules for custom games. The host picks them in the Custom Game settings panel; they travel in the lobby data
// and every player applies the same values to the map's objective data when the match world loads (before the
// match starts), so the deterministic rollback simulation stays identical on all machines.
#include <windows.h>
#include <map>
#include <set>
#include <string>
#include <cstdio>
#include <algorithm>
#include <cwctype>
#include <cwchar>
#include "MinHook.h"
#include "uobj.h"
#include "mod.h"

namespace rules {
namespace {
// Options shown in the settings rows (index -> value). Index 'kDefault*' leaves the map's own value.
const wchar_t* kScoreText[] = { L"25%", L"50%", L"75%", L"Default", L"150%", L"200%", L"300%", L"500%" };
const float kScoreMul[] = { 0.25f, 0.5f, 0.75f, 1.0f, 1.5f, 2.0f, 3.0f, 5.0f };
// Map modifiers (ids from the game's map mod list) and their names in the settings panel.
const wchar_t* kModIds[] = { L"DoubleDamage", L"SuperPowered", L"Killstreak", L"ExplodeOnDeath", L"CellPowerup", L"AllObjectives",
                             L"Barriers", L"PowerZones", L"SingleObjective", L"Slime", L"SpeedPads", L"VIP" };
const wchar_t* kModNames[] = { L"Double Damage", L"Super Powered", L"Killstreaks", L"Explode on Death", L"Cell Powerups",
                               L"All Objectives", L"Barriers", L"Power Zones", L"Single Objective", L"Slime", L"Speed Pads", L"VIP" };
constexpr int kNumMods = sizeof(kModIds) / sizeof(kModIds[0]);
constexpr uintptr_t A_ActiveModsCVarValue = 0x145341278;   // FString* of the MapMods.ActiveMapMods console variable
constexpr uintptr_t A_ModsFromCVar = 0x14102c6b0;          // bool UMBMapModsManager::TrySetActiveMapModsFromCVar()
constexpr uintptr_t A_ModsWorldInit = 0x14101a6d0;         // UMBMapModsManager world init (reads the CVar offline only)
constexpr int kScoreDefault = 3;
const wchar_t* kObjText[] = { L"Default", L"Fast", L"Slow", L"Fixed" };   // objective rotation
const float kObjMul[] = { 1.0f, 0.5f, 2.0f, 0.0f };
const wchar_t* kCapText[] = { L"Default", L"Fast", L"Slow" };             // capture speed
const float kCapMul[] = { 1.0f, 0.5f, 2.0f };
const wchar_t* kTeamText[] = { L"1v1", L"2v2", L"3v3", L"4v4" };

Values gCur;                       // current rules (host: from the panel; members: from the lobby)
uo::UObject* gAppliedWorld;
std::map<uo::UObject*, std::pair<int, float>> gOrigPoints;   // points manager data -> (PointsRequiredToWin, CycleActiveTime)
std::map<uo::UObject*, float> gOrigCapture;                    // capture point data -> CaptureTime
std::map<uo::UObject*, int> gOrigSeeds;

// MBCapturePointManagerData / MBCapturePointData / MBSeedManagerActorData fields
constexpr size_t PMD_PointsRequiredToWin = 0x4c, PMD_InfiniteCycle = 0x98, PMD_CycleActiveTime = 0x9c;
constexpr size_t CPD_CaptureTime = 0x220;
}  // namespace

const wchar_t* const* ScoreOptions(int* n) { *n = 8; return kScoreText; }
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
                            for (auto& c : n) { c = start ? towupper(c) : towlower(c); start = c == L' '; }
                            for (const wchar_t* w : { L" Of ", L" The ", L" On " }) {
                                size_t p = n.find(w);
                                if (p != std::wstring::npos) for (size_t q = p + 1; q < p + wcslen(w) - 1; q++) n[q] = towlower(n[q]);
                            }
                            names[j] = n;
                        }
                    }
            }
            for (int j = 0; j < kNumMods; j++) Log("rules: map mod %ls = '%ls'", kModIds[j], names[j].c_str());
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
// The map mods manager reads the console variable only in offline play; custom games read it on every machine,
// so host and members run the same modifiers in the deterministic simulation.
using WorldInitFn = void(__fastcall*)(void*, void*);
WorldInitFn oModsWorldInit;
void __fastcall hkModsWorldInit(void* mgr, void* worldRef) {
    if (lobby::Active() && gCur.mods) {
        std::wstring list = ModList(gCur.mods);
        SetModsCVar(list);
        bool ok = Fn<bool(__fastcall*)(void*)>(A_ModsFromCVar)(mgr);
        Log("rules: map mods '%ls' -> %d", list.c_str(), ok);
    } else SetModsCVar(L"");
    oModsWorldInit(mgr, worldRef);
}
void Install() {
    MH_CreateHook((void*)VA(A_ModsWorldInit), (void*)&hkModsWorldInit, (void**)&oModsWorldInit);
}
const wchar_t* const* ObjectiveOptions(int* n) { *n = 4; return kObjText; }
const wchar_t* const* CaptureOptions(int* n) { *n = 3; return kCapText; }
const wchar_t* const* TeamSizeOptions(int* n) { *n = 4; return kTeamText; }

Values Current() { return gCur; }
void Set(const Values& v) {
    if (v.score != gCur.score || v.objectives != gCur.objectives || v.capture != gCur.capture || v.teamSize != gCur.teamSize || v.mods != gCur.mods)
        Log("rules: score=%d objectives=%d capture=%d team=%d mods=%x", v.score, v.objectives, v.capture, v.teamSize, v.mods);
    gCur = v;
}
std::string Encode() {
    char b[96]; snprintf(b, sizeof b, "%d,%d,%d,%d,%u", gCur.score, gCur.objectives, gCur.capture, gCur.teamSize, gCur.mods);
    return b;
}
Values Decode(const std::string& s) {
    Values v;
    if (!s.empty()) sscanf(s.c_str(), "%d,%d,%d,%d,%u", &v.score, &v.objectives, &v.capture, &v.teamSize, &v.mods);
    if (v.score < 0 || v.score > 7) v.score = kScoreDefault;
    v.mods &= (1u << kNumMods) - 1;
    if (v.objectives < 0 || v.objectives > 3) v.objectives = 0;
    if (v.capture < 0 || v.capture > 2) v.capture = 0;
    if (v.teamSize < 1 || v.teamSize > 4) v.teamSize = 4;
    return v;
}

// Called every tick; applies the rules once per match world as soon as the objective data exists.
void Tick() {
    if (!lobby::Active() || !net::InNetGame()) { gAppliedWorld = nullptr; return; }
    static DWORD last;
    DWORD now = GetTickCount();
    if (now - last < 500) return;
    last = now;
    std::wstring wn = net::WorldName();
    static std::wstring appliedName;
    static int passes;
    if (wn != appliedName) { appliedName = wn; passes = 0; gOrigPoints.clear(); gOrigCapture.clear(); gOrigSeeds.clear(); }
    if (passes > 20) return;   // keep re-checking for ~10 s while the level streams in
    passes++;
    for (uo::UObject* d : uo::FindAll(uo::FindClass(L"MBCapturePointManagerData"))) {
        if (!gOrigPoints.count(d)) gOrigPoints[d] = { F<int32_t>(d, PMD_PointsRequiredToWin), F<float>(d, PMD_CycleActiveTime) };
        auto o = gOrigPoints[d];
        F<int32_t>(d, PMD_PointsRequiredToWin) = std::max(1, (int)(o.first * kScoreMul[gCur.score] + 0.5f));
        if (kObjMul[gCur.objectives] == 0.0f) F<bool>(d, PMD_InfiniteCycle) = true;
        else F<float>(d, PMD_CycleActiveTime) = o.second * kObjMul[gCur.objectives];
        if (passes == 1) Log("rules: %ls points %d -> %d, cycle %.0f", uo::Name(d).c_str(), o.first, F<int32_t>(d, PMD_PointsRequiredToWin), F<float>(d, PMD_CycleActiveTime));
    }
    for (uo::UObject* d : uo::FindAll(uo::FindClass(L"MBCapturePointData"))) {
        if (!gOrigCapture.count(d)) gOrigCapture[d] = F<float>(d, CPD_CaptureTime);
        F<float>(d, CPD_CaptureTime) = gOrigCapture[d] * kCapMul[gCur.capture];
    }
}

void ApplyOnMapLoad() {}
}  // namespace rules
