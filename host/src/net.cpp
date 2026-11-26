// Listen server support: reimplements UWorld::Listen, which the Client build compiled to "return false".
#include <windows.h>
#include <string>
#include <cstring>
#include "MinHook.h"
#include "ue.h"
#include "uobj.h"
#include "mod.h"

static void* FindActiveNetDriver(void* world, int32_t name) {
    void* engine = *(void**)VA(Addr::GEngine);
    auto& list = F<TArray<uint8_t*>>(engine, Off::Engine_WorldList);
    for (int i = 0; i < list.Num; i++) {
        uint8_t* ctx = list.Data[i];
        if (!ctx || F<void*>(ctx, Off::Ctx_World) != world) continue;
        auto& nds = F<TArray<void*[2]>>(ctx, Off::Ctx_ActiveNetDrivers);
        for (int j = 0; j < nds.Num; j++) {
            void* nd = nds.Data[j][0];
            if (nd && F<FName>(nd, Off::ND_NetDriverName).Index == name) return nd;
        }
    }
    return nullptr;
}

// bool UWorld::Listen(FURL& URL)
static bool __fastcall WorldListen(void* world, void* url) {
    Log("Listen requested (world=%p)", world);
    if (F<void*>(world, Off::World_NetDriver)) { Log("  already has a NetDriver"); return false; }
    void* engine = *(void**)VA(Addr::GEngine);
    auto create = Fn<bool(__fastcall*)(void*, void*, uint64_t, uint64_t)>(Addr::CreateNamedNetDriver_World);
    if (!create(engine, world, NameArg(NAME_GameNetDriver), NameArg(NAME_GameNetDriver))) { Log("  CreateNamedNetDriver failed"); return false; }
    void* nd = FindActiveNetDriver(world, NAME_GameNetDriver);
    if (!nd) { Log("  net driver not found after creation"); return false; }
    F<void*>(world, Off::World_NetDriver) = nd;
    Fn<void(__fastcall*)(void*, void*)>(Addr::NetDriver_SetWorld)(nd, world);
    auto coll = Fn<uint8_t*(__fastcall*)(void*, int)>(Addr::World_FindOrAddCollectionByType);
    F<void*>(coll(world, 0), Off::LevelCollection_NetDriver) = nd;   // DynamicSourceLevels
    F<void*>(coll(world, 2), Off::LevelCollection_NetDriver) = nd;   // StaticLevels
    FString err;
    void** vt = *(void***)nd;
    auto initListen = (bool(__fastcall*)(void*, void*, void*, bool, FString*))vt[Slot::InitListen];
    bool ok = initListen(nd, (uint8_t*)world + Off::World_NetworkNotify, url, false, &err);
    Log("  InitListen(%p, vt=%p) -> %d err='%ls' port=%d", nd, (void*)((uintptr_t)vt - gBase + 0x140000000), ok, err.c_str(), F<int32_t>(url, 0x20));
    if (!ok) {
        F<void*>(world, Off::World_NetDriver) = nullptr;
        return false;
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// Travel. Lobby code (or the dev command-line flags) asks for a travel; it is queued on the world context exactly like
// UEngine::SetClientTravel does. Joins retry every 8 s while the host is still loading, for up to 90 s.
namespace {
constexpr uintptr_t TickWorldTravel = 0x1425ee300;   // void UEngine::TickWorldTravel(FWorldContext&, float)
constexpr uintptr_t FMemoryRealloc = 0x141440950;    // void* FMemory::Realloc(void*, SIZE_T, uint32)
constexpr size_t Ctx_TravelURL = 0xd0;
constexpr size_t Ctx_TravelType = 0xe0;
const wchar_t* kHostURL = L"/Game/Levels/Map_Train/GameMode_CP/Map_Train_CP_Main?listen";

std::wstring gTravel;     // one-shot travel request
bool gCustomMatch;        // the current/last match was entered through the mod (not official matchmaking)
std::wstring gOurTravel;  // the travel URL we wrote last (to tell our travels from the game's own)
std::wstring gJoin;       // join target with retries, empty = none
float gReady;
DWORD gLastAttempt, gJoinStart;
int gAttempts;
uint8_t* gCtx;

using TickWorldTravelFn = void(__fastcall*)(void*, uint8_t*, float);
TickWorldTravelFn oTickWorldTravel;

void SetTravel(uint8_t* ctx, const std::wstring& url) {
    gOurTravel = url;
    if (url.find(L"FrontEnd") == std::wstring::npos) gCustomMatch = true;
    auto realloc_ = Fn<void*(__fastcall*)(void*, size_t, uint32_t)>(FMemoryRealloc);
    FString& s = F<FString>(ctx, Ctx_TravelURL);
    int32_t n = (int32_t)url.size() + 1;
    s.Data = (wchar_t*)realloc_(s.Data, n * sizeof(wchar_t), 0);
    memcpy(s.Data, url.c_str(), n * sizeof(wchar_t));
    s.Num = s.Max = n;
    F<uint8_t>(ctx, Ctx_TravelType) = 0;   // TRAVEL_Absolute
}
void* CtxWorld() { return gCtx ? F<void*>(gCtx, Off::Ctx_World) : nullptr; }
void* WorldND() { void* w = CtxWorld(); return w ? F<void*>(w, Off::World_NetDriver) : nullptr; }
}  // namespace

void GameTick(float dt);   // be1v1.cpp
namespace {
void __fastcall hkTickWorldTravel(void* engine, uint8_t* ctx, float dt) {
    gCtx = ctx;
    GameTick(dt);
    // A travel to a map that the mod didn't ask for is official matchmaking: its leaves count again.
    {
        FString& tu = F<FString>(ctx, Ctx_TravelURL);
        if (tu.Num > 1 && gOurTravel != tu.c_str() && !wcsstr(tu.c_str(), L"FrontEnd") && gCustomMatch) {
            Log("travel by the game to %ls: official match", tu.c_str());
            gCustomMatch = false;
        }
    }
    bool pendingTravel = F<FString>(ctx, Ctx_TravelURL).Num > 1 || F<void*>(ctx, Off::Ctx_PendingNetGame);
    void* w0 = F<void*>(ctx, Off::Ctx_World);
    // A loaded world: the host and offline play have a game mode, a joined player has a connection to its host.
    void* nd0 = w0 ? F<void*>(w0, Off::World_NetDriver) : nullptr;
    bool loaded = w0 && (F<void*>(w0, Off::World_AuthorityGameMode) || (nd0 && F<void*>(nd0, Off::ND_ServerConnection)));
    if (!gTravel.empty() && !pendingTravel && loaded) {
        Log("travel -> %ls", gTravel.c_str());
        SetTravel(ctx, gTravel);
        gTravel.clear();
    } else if (!gJoin.empty()) {
        void* world = F<void*>(ctx, Off::Ctx_World);
        void* nd = world ? F<void*>(world, Off::World_NetDriver) : nullptr;
        if (nd && F<void*>(nd, Off::ND_ServerConnection)) {
            Log("joined %ls after %d attempt(s)", gJoin.c_str(), gAttempts);
            gJoin.clear();
        } else {
            bool idle = world && F<void*>(world, Off::World_AuthorityGameMode) && !nd && !pendingTravel;
            gReady = idle ? gReady + dt : 0;
            DWORD now = GetTickCount();
            if (now - gJoinStart > 90000) { Log("join %ls timed out", gJoin.c_str()); gJoin.clear(); }
            // Wait for the menu world to settle; retry every 8 s (the host may still be loading).
            else if (gReady > 1.0f && (gAttempts == 0 || now - gLastAttempt > 8000)) {
                gLastAttempt = now; gAttempts++;
                Log("join attempt #%d -> %ls", gAttempts, gJoin.c_str());
                SetTravel(ctx, gJoin);
                gReady = 0;
            }
        }
    }
    oTickWorldTravel(engine, ctx, dt);
}
}  // namespace

namespace net {
void Travel(const std::wstring& url) { gJoin.clear(); gTravel = url; }
void JoinHost(const std::wstring& addr) { gTravel.clear(); gJoin = addr; gAttempts = 0; gReady = 0; gJoinStart = GetTickCount(); }
void CancelJoin() { gJoin.clear(); }
bool Joining() { return !gJoin.empty(); }
bool CustomMatch() { return gCustomMatch; }
bool InNetGame() { return WorldND() != nullptr; }
bool IsHosting() { void* nd = WorldND(); return nd && !F<void*>(nd, Off::ND_ServerConnection); }
bool IsConnectedClient() { void* nd = WorldND(); return nd && F<void*>(nd, Off::ND_ServerConnection); }
std::wstring WorldName() { void* w = CtxWorld(); return w ? uo::Name((uo::UObject*)w) : L""; }
void* World() { return CtxWorld(); }
bool InFrontend() { return WorldName() == L"Map_FrontEnd_3D"; }
bool MenuSettled() {
    if (!gCtx || !InFrontend() || WorldND()) return false;
    if (F<FString>(gCtx, Ctx_TravelURL).Num > 1 || F<void*>(gCtx, Off::Ctx_PendingNetGame)) return false;
    return gTravel.empty();
}
}  // namespace net

void InstallNet() {
    // Developer shortcuts (harness): -be1v1host[ -be1v1lan] hosts Train CP, -be1v1join=<addr> joins.
    std::wstring cmd = GetCommandLineW();
    size_t j = cmd.find(L"-be1v1join=");
    if (cmd.find(L"-be1v1host") != std::wstring::npos) {
        gJoin.clear();
        gTravel = kHostURL;
        if (cmd.find(L"-be1v1lan") != std::wstring::npos) gTravel += L"?bIsLanMatch";
    } else if (j != std::wstring::npos) {
        size_t s = j + 11, e = cmd.find_first_of(L" \"", s);
        net::JoinHost(cmd.substr(s, e == std::wstring::npos ? std::wstring::npos : e - s));
    }
    MH_CreateHook((void*)VA(TickWorldTravel), (void*)&hkTickWorldTravel, (void**)&oTickWorldTravel);
    bool ok = PatchCall(Addr::LoadMap_ListenCall, Addr::StubReturnFalse, (void*)&WorldListen);
    Log("listen patch: %d", ok);
    // UWorld::NotifyControlMessage(NMT_Hello): with an empty EncryptionToken the server checks
    // [PacketHandlerComponents] bForcePacketEncryptionInShipping and rejects with "Encryption token failure".
    // Tokens came from PlayFab matchmaking, so accept unencrypted joins: "je" -> "jmp" (go send the Challenge).
    uint8_t* p = (uint8_t*)VA(0x14262d02a);
    if (p[0] == 0x84 && p[1] == 0xC0 && p[2] == 0x74 && p[3] == 0x64) {
        uint8_t j = 0xEB; PatchBytes(p + 2, &j, 1);
        Log("encryption-token patch: 1");
    } else Log("encryption-token patch: bytes mismatch");
}
