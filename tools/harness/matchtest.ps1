param([int]$Map = 0, [string]$Rules = '', [int]$Wait = 35, [switch]$NoBoot)
# Two-player match over the dev backend: instance 1 hosts (main menu UI), instance 2 joins. Optional map index and
# rules ("cp,rotation,capture,teamsize,mods,pc,modmode", see rules::Decode). Both pick a fighter.
$H = $PSScriptRoot
$run = Join-Path $H '..\..\build\run'
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
if ($Map -ne 0) { & "$H\lua.ps1" -Code "local m = live(all('MBCustomGameManager'))[1] m.MapRoster[1] = $Map" | Out-Null }
if ($Rules) { & "$H\dev.ps1" -Cmd "lobby rules $Rules" | Out-Null }
Start-Sleep 2
& "$H\dev.ps1" -Cmd 'lobby start' | Out-Null
Start-Sleep $Wait
& "$H\pick.ps1" -Instance 1 -Hero Ninja | Out-Null
& "$H\pick.ps1" -Instance 2 -Hero Cass | Out-Null
"match running"
