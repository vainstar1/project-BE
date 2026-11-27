param([int]$Map = 0, [int]$T1 = 0, [int]$T2 = 2, [string]$Rules = '', [int]$Wait = 35, [switch]$NoBoot, [switch]$NoPick)
# Like matchtest.ps1, but forces the match team of each instance (dev override "lobby forceteam N") to test 3-4 team play.
$H = $PSScriptRoot
if (-not $NoBoot) {
    & "$H\ctl.ps1" -Action kill | Out-Null; & "$H\ctl.ps1" -Action kill -Instance 2 | Out-Null
    Remove-Item -Recurse -Force "$env:TEMP\be1v1-devlobby" -ErrorAction SilentlyContinue
    Start-Sleep 2
    & "$H\menu.ps1" -ExtraArgs '-be1v1devlobby' | Select-Object -Last 1
    & "$H\ctl.ps1" -Action boot -Instance 2 -ExtraArgs '-be1v1devlobby' | Select-Object -Last 1
}
& "$H\dev.ps1" -Cmd 'lobby create' | Out-Null
Start-Sleep 3
& "$H\dev.ps1" -Instance 2 -Cmd 'lobby join 1' | Out-Null
Start-Sleep 3
& "$H\dev.ps1" -Cmd "lobby forceteam $T1" | Out-Null
& "$H\dev.ps1" -Instance 2 -Cmd "lobby forceteam $T2" | Out-Null
if ($Map -ne 0) { & "$H\lua.ps1" -Code "local m = live(all('MBCustomGameManager'))[1] m.MapRoster[1] = $Map" | Out-Null }
if ($Rules) { & "$H\dev.ps1" -Cmd "lobby rules $Rules" | Out-Null }
Start-Sleep 2
& "$H\dev.ps1" -Cmd 'lobby start' | Out-Null
Start-Sleep $Wait
if (-not $NoPick) {
    & "$H\pick.ps1" -Instance 1 -Hero Ninja | Out-Null
    & "$H\pick.ps1" -Instance 2 -Hero Cass | Out-Null
}
"match running"
