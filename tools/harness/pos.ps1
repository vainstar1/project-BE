param([string]$Dir = 'ue4ss')
# Prints the position of every player character (proxy pawn) in an instance, on one line.
& "$PSScriptRoot\lua.ps1" -Dir $Dir -Code 'local s = "" for _, p in ipairs(live(all("MBProxyPawn"))) do local l = call(p, "K2_GetActorLocation") s = s .. fname(p):match("[^%.]+$"):gsub("_PlayerProxy_C_0", "") .. (l and string.format(" %.0f %.0f %.0f | ", l.X, l.Y, l.Z) or " ? | ") end plog("PAWNS " .. s)' | Select-String 'PAWNS ' | Select-Object -Last 1 | ForEach-Object { ($_ -split 'PAWNS ')[1] }
