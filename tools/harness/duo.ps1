param([string]$Map = '/Game/Levels/Map_Train/GameMode_CP/Map_Train_CP_Main', [int]$JoinDelay = 20, [switch]$KeepClient)
# Full local 1v1 test: instance 1 hosts (listen) and instance 2 joins over 127.0.0.1.
$H = $PSScriptRoot
& "$H\ctl.ps1" -Action kill | Out-Null
if (-not $KeepClient) { & "$H\ctl.ps1" -Action kill -Instance 2 | Out-Null }
Start-Sleep 2
& "$H\ctl.ps1" -Action boot
& "$H\lua.ps1" -Code "openmap('$($Map)?listen?bIsLanMatch')" | Out-Null
if (-not $KeepClient) { & "$H\ctl.ps1" -Action boot -Instance 2 }
Start-Sleep $JoinDelay
& "$H\lua.ps1" -Dir ue4ss2 -Code "openmap('127.0.0.1:7777')" | Out-Null
"join requested"
