# Background watcher: dismisses game-owned message boxes (e.g. the EasyAntiCheat "IGameClient" warning) for all instances.
# Exits after 30 minutes with no game process. Start once: Start-Process powershell -WindowStyle Hidden -ArgumentList '-File', 'dialogwatch.ps1'
$ctl = Join-Path $PSScriptRoot 'ctl.ps1'
$idle = 0
while ($idle -lt 900) {
    $procs = Get-Process | Where-Object { $_.ProcessName -match '^(MobladeClient|BEInstance\d+)-Win64-Shipping$' }
    if (-not $procs) { $idle++ } else { $idle = 0 }
    foreach ($p in $procs) { & $ctl -Action dismiss -TargetPid $p.Id | Out-Null }
    Start-Sleep 2
}
