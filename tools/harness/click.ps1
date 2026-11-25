param([Parameter(Mandatory = $true)][int]$X, [Parameter(Mandatory = $true)][int]$Y, [int]$Instance = 1)
# Clicks at client coordinates of the game window without touching the real cursor:
# be1v1.dll fakes GetCursorPos (dev command), then mouse messages are posted to the window.
$H = $PSScriptRoot
& "$H\dev.ps1" -Instance $Instance -Cmd "cursor $X $Y" | Out-Null
& "$H\ctl.ps1" -Action click -Instance $Instance -Keys "$X,$Y" | Out-Null
Start-Sleep -Milliseconds 300
& "$H\dev.ps1" -Instance $Instance -Cmd "cursor off" | Out-Null
"clicked $X,$Y"
