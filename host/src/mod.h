// Cross-module API of be1v1.dll.
#pragma once
#include <cstdint>
#include <string>
#include <functional>
#include <vector>

#define BE1V1_VERSION "2.2.0"
#define BE1V1_PROTOCOL "3"     // lobbies only list/accept peers with the same protocol

namespace net {
void Travel(const std::wstring& url);          // absolute travel on the next tick (menu -> map, or back to menu)
void JoinHost(const std::wstring& addr);       // connect to a host, retrying while it loads (cancelled by CancelJoin/Travel)
void CancelJoin();
bool Joining();
bool CustomMatch();                            // the current/last match was a player-hosted one (entered through the mod)
bool InNetGame();                              // world has a net driver (hosting or connected)
bool IsHosting();                              // net driver without server connection
bool IsConnectedClient();                      // net driver with a server connection
bool InFrontend();                             // the main menu world is loaded
bool MenuSettled();                            // in the menu world with no travel in progress (safe to touch UI)
std::wstring WorldName();
void* World();                                 // current UWorld
}

namespace lobby {
bool Active();                  // in a custom-game lobby
bool IsHost();
int MyTeam();                   // team for this player in the current match (-1 spectator), 0 if unknown
int PlayersInMatch();           // non-spectator players at match start
void CreateAsHost();            // from the main menu entry
void JoinById(uint64_t id);     // invite / browser / code
void Leave();
void ShowScreen();              // bring the lobby screen up (main menu)
void OnMatchEnded();            // back in the menu after a match
std::wstring StatusLine();      // short status for logs
void Tick(float dt);
void Install();
std::wstring LobbyCode();       // shareable join code for the current lobby
void SetTeamSize(int perTeam);   // host: maximum players per team
int SpectatorPlaces();          // spectator places in the lobby
void SetSpectatorPlaces(int n);  // host
void OpenInvite();              // Steam invite dialog for the current lobby
void OpenBrowser();             // CUSTOM GAME: list of joinable games + create
bool OnBackPressed();           // lobby screen back: true = handled (stay in lobby)
bool OnSlotPressed(void* slot); // team slot clicked
bool OnListButton(void* btn);   // a PromptListButton was pressed (lobby screen LEAVE)
}

namespace ui {
void Install();
void Tick(float dt);
void ShowMessage(const std::wstring& title, const std::wstring& body);   // native confirmation popup with OK
void ShowBusy(bool on);
void Ask(const std::wstring& body, const std::wstring& yes, const std::wstring& no, std::function<void(bool yes)> cb);
enum { kYes = -2, kNo = -1 };
// Message, a column of buttons, and two bottom buttons (empty label hides "yes"). cb gets the row index, kYes or kNo.
int List(const std::wstring& body, const std::vector<std::wstring>& rows, const std::wstring& yes, const std::wstring& no, std::function<void(int)> cb);
bool UpdateList(int listId, const std::vector<std::wstring>& rows);   // false once the list is gone
bool ListOpen(int listId);
void OpenOfficialCustomQueue();  // the game's own Custom Queue (official servers)
bool PromptOpen();
void FastTick();
std::wstring TextToString(const void* ftext);
void DevCommand(const char* cmd);
bool MainMenuReady();          // main menu up, title screen gone, no prompt showing
}

namespace update {
void Install();
void Tick(float dt);
bool Available();
bool Postponed();              // the player chose "Later"
void Begin();                  // download and apply, then restart the game
std::wstring LatestVersion();
}

namespace rules {
// cp / pc: points (Objective Control) and cells (Power Collection) to win, 0 = the map's own target.
// modMode: how the host picks map modifiers in the panel (0 off, 1 chosen one by one, 2 all).
struct Values { int cp = 0, objectives = 0, capture = 0, teamSize = 4; uint32_t mods = 0; int pc = 0, modMode = 0; };
int NumMods();
const wchar_t* ModName(int i);
void Install();
Values Current();
void Set(const Values& v);
std::string Encode();
Values Decode(const std::string& s);
const wchar_t* const* ObjectiveOptions(int* n);
const wchar_t* const* CaptureOptions(int* n);
const wchar_t* const* TeamSizeOptions(int* n);
const wchar_t* const* ModModeOptions(int* n);
std::vector<std::wstring> CpScoreOptions();
std::vector<std::wstring> PcScoreOptions();
int CpIndex(int value);
int PcIndex(int value);
int CpValueAt(int index);
int PcValueAt(int index);
void Tick();                 // re-applies the rules while the match world streams in
void ApplyOnMapLoad();
}

namespace settings {
void Tick();                 // adds our rows to the Custom Game settings panel and reads them (host)
void DevSetRow(int row, int index);
}

std::wstring ModDir();          // folder that holds be1v1.dll
std::wstring Utf8ToWide(const std::string& s);
std::string WideToUtf8(const std::wstring& s);
