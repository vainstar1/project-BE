param([switch]$MidMatch, [int]$Wait = 45)
# Spectator test over the dev backend: instance 1 hosts and plays, instance 2 spectates.
# -MidMatch: instance 2 joins the lobby only after the match started, then switches to spectator and drops in.
$H = $PSScriptRoot
$run = "$H\..\..\build\run"
& "$H\ctl.ps1" -Action kill | Out-Null; & "$H\ctl.ps1" -Action kill -Instance 2 | Out-Null
Remove-Item -Recurse -Force "$env:TEMP\be1v1-devlobby" -ErrorAction SilentlyContinue
Start-Sleep 2
& "$H\menu.ps1" -ExtraArgs '-be1v1devlobby' | Select-Object -Last 1
& "$H\ctl.ps1" -Action boot -Instance 2 -ExtraArgs '-be1v1devlobby' | Select-Object -Last 1
& "$H\dev.ps1" -Cmd 'lobby create' | Out-Null
Start-Sleep 3
if (-not $MidMatch) {
    & "$H\dev.ps1" -Instance 2 -Cmd 'lobby join 1' | Out-Null
    Start-Sleep 3
    & "$H\dev.ps1" -Instance 2 -Cmd 'lobby team -1' | Out-Null
    Start-Sleep 2
}
& "$H\dev.ps1" -Cmd 'lobby start' | Out-Null
Start-Sleep 30
& "$H\pick.ps1" -Instance 1 -Hero Ninja | Out-Null
function WaitLog([int]$Inst, [string]$Pattern, [int]$Secs = 60) {
    $name = if ($Inst -eq 1) { 'MobladeClient-Win64-Shipping' } else { "BEInstance$Inst-Win64-Shipping" }
    $p = Get-Process -Name $name | Select-Object -First 1
    $log = Join-Path $run "be1v1-$($p.Id).log"
    $start = (Get-Content $log).Count
    $deadline = (Get-Date).AddSeconds($Secs)
    while ((Get-Date) -lt $deadline) {
        if ((Get-Content $log | Select-Object -Skip $start) -match $Pattern) { return $true }
        Start-Sleep 1
    }
    "timeout waiting for $Pattern"; return $false
}
if ($MidMatch) {
    Start-Sleep 10
    & "$H\dev.ps1" -Instance 2 -Cmd 'lobby join 1' | Out-Null
    WaitLog 2 'adding local player' 60 | Out-Null
    & "$H\dev.ps1" -Instance 2 -Cmd 'lobby team -1' | Out-Null
    Start-Sleep 2
    # it joined the running match as a player: go back and drop in again as a spectator
    & "$H\dev.ps1" -Instance 2 -Cmd 'lobby tomenu' | Out-Null
    WaitLog 2 'back in the menu' 60 | Out-Null
    & "$H\dev.ps1" -Instance 2 -Cmd 'lobby rejoin' | Out-Null
}
Start-Sleep $Wait
& "$H\ctl.ps1" -Action shot -Instance 2 -Out "$env:TEMP\claude\spec2.png" | Out-Null
& "$H\ctl.ps1" -Action shot -Out "$env:TEMP\claude\spec1.png" | Out-Null
foreach ($f in (Get-ChildItem "$run\be1v1-*.log" | Sort-Object LastWriteTime | Select-Object -Last 2)) {
    "== $($f.Name)"; Get-Content $f.FullName | Select-String "spectat|teams:|joined|EXC|lobby: match|adding local" | Select-Object -Last 12
}
