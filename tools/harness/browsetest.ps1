param([switch]$NoBoot)
# Member flow over the local dev backend: instance 2 hosts; instance 1 (main menu) opens CUSTOM GAME, picks the game
# with the keyboard, goes BACK to the main menu (staying in the lobby), returns, switches team by pressing a slot, leaves.
$H = $PSScriptRoot
$shots = "$env:TEMP\claude"
function Log1 { $p = (Get-Process MobladeClient-Win64-Shipping).Id; Get-Content "$H\..\..\build\run\be1v1-$p.log" | Select-String $args[0] | Select-Object -Last $args[1] | ForEach-Object { $_.Line } }
if (-not $NoBoot) {
    & "$H\ctl.ps1" -Action kill | Out-Null; & "$H\ctl.ps1" -Action kill -Instance 2 | Out-Null
    Remove-Item -Recurse -Force "$env:TEMP\be1v1-devlobby" -ErrorAction SilentlyContinue
    Start-Sleep 2
    & "$H\menu.ps1" -ExtraArgs '-be1v1devlobby' | Select-Object -Last 1
    & "$H\ctl.ps1" -Action boot -Instance 2 -ExtraArgs '-be1v1devlobby' | Select-Object -Last 1
}
& "$H\dev.ps1" -Instance 2 -Cmd 'lobby create' | Out-Null
Start-Sleep 3
"--- browse + join"
& "$H\lua.ps1" -Code 'call(live(all("FE_MainMenuScreen_C"))[1], "OnCustomQueuePressed")' | Out-Null
Start-Sleep 3
& "$H\ctl.ps1" -Action shot -Out "$shots\bt0.png" | Out-Null
& "$H\ctl.ps1" -Action post -Keys '28' | Out-Null; Start-Sleep 1
& "$H\ctl.ps1" -Action post -Keys '20' | Out-Null; Start-Sleep 5
& "$H\ctl.ps1" -Action shot -Out "$shots\bt1.png" | Out-Null
Log1 'lobby:|prompt closed' 3
"--- back (Esc) keeps the lobby"
& "$H\ctl.ps1" -Action post -Keys '1B' | Out-Null; Start-Sleep 3
& "$H\ctl.ps1" -Action shot -Out "$shots\bt2.png" | Out-Null
Log1 'lobby:' 2
"--- CUSTOM GAME returns to the lobby"
& "$H\lua.ps1" -Code 'call(live(all("FE_MainMenuScreen_C"))[1], "OnCustomQueuePressed")' | Out-Null; Start-Sleep 3
& "$H\ctl.ps1" -Action shot -Out "$shots\bt3.png" | Out-Null
"--- press an empty team-0 slot"
& "$H\dev.ps1" -Cmd 'ui slot 0 empty' | Out-Null
Start-Sleep 3
Get-Content "$env:TEMP\be1v1-devlobby\lobby.kv" | Select-String '^teams'
& "$H\ctl.ps1" -Action shot -Out "$shots\bt4.png" | Out-Null
"--- LEAVE"
& "$H\dev.ps1" -Cmd 'ui press Debug_UpdateSessionData' | Out-Null
Start-Sleep 2
& "$H\ctl.ps1" -Action shot -Out "$shots\bt5.png" | Out-Null
Log1 'lobby:' 2
