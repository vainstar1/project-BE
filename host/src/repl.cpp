// Server-side actor replication. The Client build compiled UNetDriver::ServerReplicateActors to "return 0" and
// removed its call from UNetDriver::TickFlush, so the host drives replication itself from a TickFlush hook,
// using the engine's own per-actor routine (the one the replay recorder uses).
#include <windows.h>
#include <vector>
#include "ue.h"


namespace {
constexpr uintptr_t A_CallPreReplication = 0x142041450;   // void AActor::CallPreReplication(UNetDriver*)
constexpr uintptr_t A_ReplicateActorTo = 0x142204330;     // bool (UNetDriver*, AActor*, UNetConnection*, bool) - find/create channel + ReplicateActor
constexpr int Slot_TickFlush = 88;
constexpr size_t ND_ReplicationFrame = 0x348;
constexpr size_t Level_Actors = 0xa0;
constexpr size_t Actor_RepFlags = 0x81;      // bit 2 = bReplicates
constexpr size_t Actor_RemoteRole = 0x85;

using TickFlushFn = void(__fastcall*)(void*, float);
TickFlushFn gOrigTickFlush;
float gAccum;
uint64_t gTicks;

void ReplicateTick(void* nd) {
    F<uint32_t>(nd, ND_ReplicationFrame)++;
    void* world = F<void*>(nd, Off::ND_World);
    if (!world) return;
    auto& conns = F<TArray<void*>>(nd, Off::ND_ClientConnections);
    std::vector<void*> ready;
    for (int i = 0; i < conns.Num; i++) {
        void* c = conns.Data[i];
        if (c && F<void*>(c, Off::Conn_OwningActor) && F<void*>(c, Off::Conn_PlayerController)) ready.push_back(c);
    }
    if (ready.empty()) return;

    auto preRep = Fn<void(__fastcall*)(void*, void*)>(A_CallPreReplication);
    auto repTo = Fn<bool(__fastcall*)(void*, void*, void*, bool)>(A_ReplicateActorTo);
    auto& levels = F<TArray<void*>>(world, Off::World_Levels);
    int considered = 0, sent = 0;
    for (int l = 0; l < levels.Num; l++) {
        void* level = levels.Data[l];
        if (!level) continue;
        auto& actors = F<TArray<void*>>(level, Level_Actors);
        for (int a = 0; a < actors.Num; a++) {
            void* actor = actors.Data[a];
            if (!actor) continue;
            if (!(F<uint8_t>(actor, Actor_RepFlags) & 4) || F<uint8_t>(actor, Actor_RemoteRole) == 0) continue;
            considered++;
            preRep(actor, nd);
            for (void* c : ready)
                if (repTo(nd, actor, c, false)) sent++;
        }
    }
    if ((gTicks % 300) == 0)
        Log("replicate: frame=%u conns=%zu levels=%d actors=%d sent=%d", F<uint32_t>(nd, ND_ReplicationFrame), ready.size(), levels.Num, considered, sent);
    gTicks++;
}

void __fastcall TickFlushHook(void* nd, float dt) {
    if (!F<void*>(nd, Off::ND_ServerConnection) && F<TArray<void*>>(nd, Off::ND_ClientConnections).Num > 0) {
        void* world = F<void*>(nd, Off::ND_World);
        if (world && F<void*>(world, Off::World_NetDriver) == nd) {
            gAccum += dt;
            if (gAccum >= 1.0f / 60.0f) { gAccum = 0; ReplicateTick(nd); }
        }
    }
    gOrigTickFlush(nd, dt);
}
}  // namespace

void InstallRepl() {
    void* orig = nullptr;
    PatchVtable(Addr::VT_IpNetDriver, Slot_TickFlush, (void*)&TickFlushHook, &orig);
    gOrigTickFlush = (TickFlushFn)orig;
    void* orig2 = nullptr;
    PatchVtable(Addr::VT_SteamNetDriver, Slot_TickFlush, (void*)&TickFlushHook, &orig2);
    Log("repl patch installed (TickFlush ip=%p steam=%p)", orig, orig2);
}
