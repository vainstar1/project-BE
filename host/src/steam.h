// Thin wrapper over the game's own steam_api64.dll (Steamworks SDK 1.39 flat API), resolved at runtime.
// All calls on the game thread. The game's OnlineSubsystemSteam initialises Steam and pumps SteamAPI_RunCallbacks.
#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <functional>

namespace steam {
bool Ready();                 // Steam API initialised and interfaces resolved
uint64_t MyId();
std::wstring MyName();
std::wstring NameOf(uint64_t id);
void RequestInfo(uint64_t id);

enum LobbyType { Private = 0, FriendsOnly = 1, Public = 2, Invisible = 3 };
// Async operations complete through the callbacks (polled each tick in steam::Tick).
void CreateLobby(LobbyType type, int maxMembers, std::function<void(bool ok, uint64_t lobby)> done);
void JoinLobby(uint64_t lobby, std::function<void(bool ok, uint64_t lobby, int response)> done);
void RequestLobbyList(const std::vector<std::pair<std::string, std::string>>& stringFilters, std::function<void(std::vector<uint64_t>)> done);
void LeaveLobby(uint64_t lobby);
bool SetLobbyData(uint64_t lobby, const char* key, const std::string& value);
std::string LobbyData(uint64_t lobby, const char* key);
void SetMemberData(uint64_t lobby, const char* key, const std::string& value);
std::string MemberData(uint64_t lobby, uint64_t member, const char* key);
std::vector<uint64_t> Members(uint64_t lobby);
uint64_t Owner(uint64_t lobby);
bool SetOwner(uint64_t lobby, uint64_t member);
void SetLobbyType(uint64_t lobby, LobbyType t);
void SetJoinable(uint64_t lobby, bool joinable);
void SetMemberLimit(uint64_t lobby, int n);
int MemberLimit(uint64_t lobby);
void RequestLobbyData(uint64_t lobby);
bool InviteUser(uint64_t lobby, uint64_t user);
void OpenInviteOverlay(uint64_t lobby);
void OpenOverlayToUser(const char* dialog, uint64_t user);
void SetRichPresence(const char* key, const char* value);
void ClearRichPresence();

// Friends currently playing this game (for the in-game invite list).
struct Friend { uint64_t id; std::wstring name; bool inGame; uint64_t lobby; };
std::vector<Friend> Friends();

// Fired when the player accepts a lobby invite or clicks "Join Game" in Steam while the game runs.
void OnJoinRequested(std::function<void(uint64_t lobby)> cb);

void Tick();   // completes async calls
bool AvatarRGBA(uint64_t id, std::vector<uint8_t>& rgba, int& w, int& h);   // false until Steam has it
}  // namespace steam
