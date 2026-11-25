#pragma once
#include <cstdint>
#include <cstddef>

extern uintptr_t gBase;
void Log(const char* fmt, ...);
bool PatchBytes(void* dst, const void* src, size_t n);
bool PatchCall(uintptr_t siteVa, uintptr_t expectVa, void* fn);
bool PatchVtable(uintptr_t vtableVa, int slot, void* fn, void** orig);

// Converts a VA from the on-disk image (base 0x140000000) to the live address.
inline uintptr_t VA(uintptr_t va) { return gBase + (va - 0x140000000ull); }
template <class T> inline T Fn(uintptr_t va) { return (T)VA(va); }
template <class T> inline T& F(void* obj, size_t off) { return *(T*)((uint8_t*)obj + off); }

struct FName { int32_t Index; int32_t Number; };
static_assert(sizeof(FName) == 8, "FName");
inline uint64_t NameArg(int32_t idx) { return (uint32_t)idx; }   // FName passed by value in a register

template <class T> struct TArray { T* Data; int32_t Num; int32_t Max; };
struct FString {
    wchar_t* Data = nullptr; int32_t Num = 0; int32_t Max = 0;
    const wchar_t* c_str() const { return Data ? Data : L""; }
};

// Hardcoded EName indices (UE 4.20 UnrealNames.inl)
enum : int32_t { NAME_GameNetDriver = 282, NAME_PendingNetDriver = 283 };

namespace Off {
// UWorld
constexpr size_t World_NetDriver = 0x38;
constexpr size_t World_AuthorityGameMode = 0x140;
constexpr size_t World_GameState = 0x148;
constexpr size_t World_Levels = 0x160;
constexpr size_t World_LevelCollections = 0x170;
constexpr size_t World_NetworkNotify = 0x28;   // FNetworkNotify base subobject
// FLevelCollection
constexpr size_t LevelCollection_NetDriver = 0x10;
// UEngine
constexpr size_t Engine_WorldList = 0xbb8;      // TIndirectArray<FWorldContext>
// FWorldContext
constexpr size_t Ctx_PendingNetGame = 0x1c8;
constexpr size_t Ctx_ActiveNetDrivers = 0x248; // TArray<FNamedNetDriver{UNetDriver*,Def*}>
constexpr size_t Ctx_World = 0x288;
// UNetDriver
constexpr size_t ND_ServerConnection = 0x88;
constexpr size_t ND_ClientConnections = 0x90;
constexpr size_t ND_World = 0xc8;
constexpr size_t ND_NetDriverName = 0x118;
constexpr size_t ND_Time = 0x168;
// UNetConnection
constexpr size_t Conn_PlayerController = 0x30;  // UPlayer::PlayerController
constexpr size_t Conn_Driver = 0x58;
constexpr size_t Conn_PackageMap = 0x68;
constexpr size_t Conn_OpenChannels = 0x70;
constexpr size_t Conn_ViewTarget = 0x90;
constexpr size_t Conn_OwningActor = 0x98;
}

namespace Addr {
constexpr uintptr_t GEngine = 0x14558F8B0;
constexpr uintptr_t CreateNamedNetDriver_World = 0x1425c8550;  // bool(UEngine*, UWorld*, FName, FName)
constexpr uintptr_t NetDriver_SetNetDriverName = 0x14237dfb0;  // void(UNetDriver*, FName)
constexpr uintptr_t NetDriver_SetWorld = 0x14237e2f0;          // void(UNetDriver*, UWorld*)
constexpr uintptr_t World_FindOrAddCollectionByType = 0x1426262f0; // FLevelCollection*(UWorld*, int)
constexpr uintptr_t LoadMap_ListenCall = 0x1425e0537;          // call UWorld::Listen (stub) in UEngine::LoadMap
constexpr uintptr_t StubReturnFalse = 0x1402ec800;
// vtables
constexpr uintptr_t VT_NetDriver = 0x143FDC328;
constexpr uintptr_t VT_IpNetDriver = 0x143489140;
constexpr uintptr_t VT_SteamNetDriver = 0x1436BF3F0;
constexpr uintptr_t VT_DemoNetDriver = 0x143F5EE28;
}
namespace Slot {
constexpr int InitConnect = 74;
constexpr int InitListen = 75;
constexpr int ServerReplicateActors = 85;
}
