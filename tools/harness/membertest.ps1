param([switch]$NoBoot)
# Member-side lobby test: instance 2 (title screen, no Steam) hosts over the dev backend, instance 1 (main menu) joins.
$H = $PSScriptRoot
if (-not $NoBoot) {
    & "$H\ctl.ps1" -Action kill | Out-Null; & "$H\ctl.ps1" -Action kill -Instance 2 | Out-Null
    Remove-Item -Recurse -Force "$env:TEMP\be1v1-devlobby" -ErrorAction SilentlyContinue
    Start-Sleep 2
    & "$H\menu.ps1" -ExtraArgs '-be1v1devlobby' | Select-Object -Last 1
    & "$H\ctl.ps1" -Action boot -Instance 2 -ExtraArgs '-be1v1devlobby' | Select-Object -Last 1
}
& "$H\dev.ps1" -Instance 2 -Cmd 'lobby create' | Select-String 'lobby:'
Start-Sleep 3
& "$H\dev.ps1" -Cmd 'lobby join 1' | Select-String 'lobby:'
Start-Sleep 4
"member lobby ready"
