param([string]$State = 'InProgress', [int]$Timeout = 90, [string]$Dir = 'ue4ss')
# Waits until the host's rollback game mode reports the given match state.
$end = (Get-Date).AddSeconds($Timeout)
while ((Get-Date) -lt $end) {
    $r = & "$PSScriptRoot\lua.ps1" -Dir $Dir -Code 'local gm = live(all("MBRollbackGameMode"))[1] plog("STATE " .. tostr(gm and call(gm, "GetRollbackMatchState")))' | Select-String 'STATE ' | Select-Object -Last 1
    if ("$r" -match "STATE $State") { "state $State"; return }
    Start-Sleep 3
}
"timeout waiting for $State (last: $r)"
