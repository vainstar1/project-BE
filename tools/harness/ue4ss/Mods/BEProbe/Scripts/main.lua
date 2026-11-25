-- BEProbe: read-mostly feasibility probe with a file command channel.
-- Write Lua into cmd.txt (next to UE4SS.dll); it runs on the game thread and output goes to probe.log.
-- ROOT is the UE4SS folder this copy was loaded from (instance 2 has its own copy).
local ROOT = [[C:\Users\andre\OneDrive\Desktop\big folder\! BE 1v1s\tools\harness\ue4ss\]]
do
    local src = debug.getinfo(1, "S").source or ""
    local dir = src:gsub("^@", ""):gsub("/", "\\"):match("^(.*\\)Mods\\BEProbe\\Scripts\\main%.lua$")
    if dir then ROOT = dir end
end
local LOGF = ROOT .. "probe.log"
local CMDF = ROOT .. "cmd.txt"

local function log(...)
    local parts = {}
    for i = 1, select("#", ...) do parts[#parts + 1] = tostring(select(i, ...)) end
    local line = os.date("%H:%M:%S ") .. table.concat(parts, " ")
    print("[BEProbe] " .. line .. "\n")
    local f = io.open(LOGF, "a")
    if f then f:write(line .. "\n") f:close() end
end
_G.plog = log

local function ok(o) return o ~= nil and o.IsValid ~= nil and o:IsValid() end
_G.ok = ok
local function fname(o) if not ok(o) then return "<nil>" end local s, r = pcall(function() return o:GetFullName() end) return s and r or "<?>" end
_G.fname = fname
local function cls(o) if not ok(o) then return "<nil>" end local s, r = pcall(function() return o:GetClass():GetFullName() end) return s and r or "<?>" end
_G.cls = cls
local function tostr(v)
    if v == nil then return "nil" end
    local t = type(v)
    if t == "userdata" then
        local s, r = pcall(function() return v:ToString() end)
        if s and r then return r end
        if v.IsValid ~= nil then return fname(v) end
    end
    return tostring(v)
end
_G.tostr = tostr
local function get(o, prop) local s, r = pcall(function() return o[prop] end) if s then return r end return "<err:" .. tostring(r) .. ">" end
_G.get = get
local function call(o, fn, ...) local args = { ... } local s, r = pcall(function() return o[fn](o, table.unpack(args)) end) if s then return r end return "<err:" .. tostring(r) .. ">" end
_G.call = call
local function all(c) local s, r = pcall(FindAllOf, c) if s and r then return r end return {} end
_G.all = all
local function live(list)
    local out = {}
    for _, o in pairs(list) do
        if ok(o) and not fname(o):find("Default__", 1, true) then out[#out + 1] = o end
    end
    return out
end
_G.live = live

local function arr(a)
    local out = {}
    if a == nil or type(a) ~= "userdata" then return out end
    pcall(function() a:ForEach(function(i, e) out[#out + 1] = e:get() end) end)
    return out
end
_G.arr = arr

function _G.world()
    for _, gi in pairs(live(all("MBGameInstance"))) do
        local w = gi:GetWorld()
        if ok(w) then return w, gi end
    end
end

function _G.snapshot(label)
    log("===== SNAPSHOT " .. tostring(label) .. " =====")
    local w, gi = world()
    log("world", fname(w))
    local K = StaticFindObject("/Script/Engine.Default__KismetSystemLibrary")
    if ok(K) and ok(w) then
        log("IsServer", call(K, "IsServer", w), "IsDedicated", call(K, "IsDedicatedServer", w), "IsStandalone", call(K, "IsStandalone", w))
    end
    if ok(w) then log("World.NetDriver", tostr(get(w, "NetDriver")), "DemoNetDriver", tostr(get(w, "DemoNetDriver"))) end
    for _, nd in pairs(live(all("NetDriver"))) do log("NetDriver", cls(nd), fname(nd)) end
    for _, gm in pairs(live(all("GameModeBase"))) do
        log("GameMode", cls(gm))
        if cls(gm):find("Rollback") then
            log("  MatchState", tostr(call(gm, "GetRollbackMatchState")), "bManualMatchStart", tostr(get(gm, "bManualMatchStart")),
                "WaitingForPlayersTimeout", tostr(get(gm, "WaitingForPlayersTimeout")), "PreMatch", tostr(get(gm, "PreMatchCountdownDuration")),
                "WarmUp", tostr(get(gm, "WarmUpPhaseDuration")), "NumTravelling", tostr(get(gm, "NumTravellingPlayers")))
        end
    end
    for _, gs in pairs(live(all("GameStateBase"))) do
        log("GameState", cls(gs), "RollbackMatchState", tostr(get(gs, "RollbackMatchState")), "bCanDoServerMigration", tostr(get(gs, "bCanDoServerMigration")))
    end
    for _, ws in pairs(live(all("MBWorldSingleton"))) do
        log("WorldSingleton", fname(ws), "GameStatus", tostr(get(ws, "GameStatus")), "LocalPlayerTeam", tostr(get(ws, "LocalPlayerTeam")))
        local mg = get(ws, "MachineGroup")
        log("  MachineGroup", cls(mg), fname(mg))
        for i, m in ipairs(arr(get(ws, "Machines"))) do log("  ws.Machine", i, cls(m), "name", tostr(get(m, "MachineName"))) end
        log("  ConnectionManager", cls(get(ws, "ConnectionManager")), "ServerPlaybackManager", cls(get(ws, "ServerPlaybackManager")))
    end
    for _, m in pairs(live(all("NTRollbackMachine"))) do
        log("NTRollbackMachine", fname(m), "name", tostr(get(m, "MachineName")), "engine", fname(get(m, "RollbackEngine")), "conns", #arr(get(m, "Connections")))
    end
    for _, g in pairs(live(all("NTRollbackMachineGroup"))) do
        log("NTRollbackMachineGroup", cls(g), "machines", #arr(get(g, "Machines")), "machineConns", #arr(get(g, "MachineConnections")))
    end
    for _, e in pairs(live(all("NTRollbackEngine"))) do
        log("NTRollbackEngine", fname(e), "frame", tostr(call(e, "GetCurrentFrameNumber")), "readyPlayers", tostr(call(e, "GetNumberOfReadyPlayers")),
            "NetDriver", tostr(get(e, "NetDriver")), "openChannels", #arr(get(e, "OpenChannels")))
    end
    for _, n in pairs(live(all("NTRollbackNetworkInterface"))) do log("NTRollbackNetworkInterface", fname(n), "AvgLag", tostr(get(n, "AvgLag"))) end
    for _, c in pairs(live(all("NetConnection"))) do log("NetConnection", cls(c), fname(c)) end
    log("PlayerControllers", #live(all("PlayerController")), "PlayerStates", #live(all("PlayerState")), "ProxyCharacters", #live(all("MBProxyCharacter")))
    for _, pc in pairs(live(all("PlayerController"))) do log("  PC", cls(pc), fname(pc)) end
    for _, ps in pairs(live(all("MBPlayerStateBase"))) do log("  PS", cls(ps), "TeamId", tostr(get(ps, "TeamId")), "Name", tostr(get(ps, "PlayerName"))) end
    for _, s in pairs(live(all("MBCapturePointManagerState"))) do
        log("CapturePointState", fname(s), "active", tostr(get(s, "bIsActive")), "override", tostr(get(s, "PointsRequiredToWinOverride")))
    end
    log("===== END " .. tostring(label) .. " =====")
end

local busy = false
local function poll()
    local f = io.open(CMDF, "r")
    if not f then return end
    local code = f:read("a") f:close()
    os.remove(CMDF)
    if code == nil or code == "" then return end
    busy = true
    ExecuteInGameThread(function()
        log(">>> cmd: " .. code:sub(1, 300):gsub("\n", " | "))
        local fn, err = load(code, "cmd", "t", _G)
        if not fn then log("!!! compile error: " .. tostring(err)) busy = false return end
        local s, r = xpcall(fn, debug.traceback)
        if not s then log("!!! runtime error: " .. tostring(r)) elseif r ~= nil then log("<<< " .. tostr(r)) end
        log("<<< done")
        busy = false
    end)
end

function _G.console(cmd)
    local K = StaticFindObject("/Script/Engine.Default__KismetSystemLibrary")
    local w = world()
    local pc = nil
    for _, p in pairs(live(all("PlayerController"))) do pc = p break end
    K:ExecuteConsoleCommand(w, cmd, pc)
end

function _G.openmap(url)
    local G = StaticFindObject("/Script/Engine.Default__GameplayStatics")
    G:OpenLevel(world(), FName(url), true, "")
end

log("BEProbe loaded from " .. ROOT)
LoopAsync(1000, function()
    if not busy then pcall(poll) end
    return false
end)
