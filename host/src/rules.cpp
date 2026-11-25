// Match rules for custom games. The host picks them in the Custom Game settings panel; they travel in the lobby data
// and every player applies the same values to the map's objective data when the match world loads (before the
// match starts), so the deterministic rollback simulation stays identical on all machines.
#include <windows.h>
#include <map>
#include <set>
#include <string>
#include <cstdio>
#include "uobj.h"
#include "mod.h"

namespace rules {
namespace {
// Options shown in the settings rows (index -> value). Index 'kDefault*' leaves the map's own value.
const wchar_t* kScoreText[] = { L"25%", L"50%", L"75%", L"Default", L"150%", L"200%", L"300%" };
const float kScoreMul[] = { 0.25f, 0.5f, 0.75f, 1.0f, 1.5f, 2.0f, 3.0f };
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

const wchar_t* const* ScoreOptions(int* n) { *n = 7; return kScoreText; }
const wchar_t* const* ObjectiveOptions(int* n) { *n = 4; return kObjText; }
const wchar_t* const* CaptureOptions(int* n) { *n = 3; return kCapText; }
const wchar_t* const* TeamSizeOptions(int* n) { *n = 4; return kTeamText; }

Values Current() { return gCur; }
void Set(const Values& v) {
    if (v.score != gCur.score || v.objectives != gCur.objectives || v.capture != gCur.capture || v.teamSize != gCur.teamSize)
        Log("rules: score=%d objectives=%d capture=%d team=%d", v.score, v.objectives, v.capture, v.teamSize);
    gCur = v;
}
std::string Encode() {
    char b[64]; snprintf(b, sizeof b, "%d,%d,%d,%d", gCur.score, gCur.objectives, gCur.capture, gCur.teamSize);
    return b;
}
Values Decode(const std::string& s) {
    Values v;
    if (!s.empty()) sscanf(s.c_str(), "%d,%d,%d,%d", &v.score, &v.objectives, &v.capture, &v.teamSize);
    if (v.score < 0 || v.score > 6) v.score = kScoreDefault;
    if (v.objectives < 0 || v.objectives > 3) v.objectives = 0;
    if (v.capture < 0 || v.capture > 2) v.capture = 0;
    if (v.teamSize < 1 || v.teamSize > 4) v.teamSize = 4;
    return v;
}

// Called every tick; applies the rules once per match world as soon as the objective data exists.
void Tick() {
    if (!lobby::Active() || !net::InNetGame()) { gAppliedWorld = nullptr; return; }
    uo::UObject* world = nullptr;
    if (uo::UObject* gi = uo::FindTransient(uo::FindClass(L"MBGameInstance"))) (void)gi;
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
    (void)world;
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
