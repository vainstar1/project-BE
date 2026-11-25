param([switch]$NoBoot, [int]$Map = -1, [switch]$Start, [int]$Wait = 40)
# Two-instance custom-game lobby test over the local dev backend (-be1v1devlobby, 127.0.0.1):
# instance 1 reaches the main menu and creates a lobby through the menu entry, instance 2 joins it.
$H = $PSScriptRoot
if (-not $NoBoot) {
    & "$H\ctl.ps1" -Action kill | Out-Null; & "$H\ctl.ps1" -Action kill -Instance 2 | Out-Null
    Remove-Item -Recurse -Force "$env:TEMP\be1v1-devlobby" -ErrorAction SilentlyContinue
    Start-Sleep 2
    & "$H\menu.ps1" -ExtraArgs '-be1v1devlobby' | Select-Object -Last 1
    & "$H\ctl.ps1" -Action boot -Instance 2 -ExtraArgs '-be1v1devlobby' | Select-Object -Last 1
}
& "$H\lua.ps1" -Code 'call(live(all("FE_MainMenuScreen_C"))[1], "OnCustomQueuePressed")' | Out-Null
Start-Sleep 3
& "$H\dev.ps1" -Instance 2 -Cmd 'lobby join 1' | Select-String 'lobby:'
Start-Sleep 3
if ($Map -ge 0) { & "$H\lua.ps1" -Code "local m = live(all('MBCustomGameManager'))[1] m.MapRoster[1] = $Map" | Out-Null; Start-Sleep 1 }
if ($Start) {
    & "$H\lua.ps1" -Code 'cgpress("start")' | Out-Null
    Start-Sleep $Wait
    & "$H\ctl.ps1" -Action shot -Out "$env:TEMP\claude\t1.png" | Out-Null
    & "$H\ctl.ps1" -Action shot -Instance 2 -Out "$env:TEMP\claude\t2.png" | Out-Null
    foreach ($f in (Get-ChildItem "$H\..\..\build\run\be1v1-*.log" | Sort-Object LastWriteTime | Select-Object -Last 2)) { "== $($f.Name)"; Get-Content $f.FullName | Select-String "lobby: [^h]|travel|joined|EXC|team" | Select-Object -Last 5 }
}
"lobby ready"
