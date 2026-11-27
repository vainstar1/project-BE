# After captest.ps1 (team 2 holds the centre point): Cass steps off, Daemon (team 0) walks onto it to take it.
$H = $PSScriptRoot
& "$H\steer.ps1" -Instance 2 -Pawn Cass -X 0 -Y 1600 -Tries 8 | Select-Object -Last 1
& "$H\ctl.ps1" -Action hold -Keys "41,450" | Out-Null
& "$H\ctl.ps1" -Action hold -Keys "57,2500" | Out-Null
& "$H\steer.ps1" -Instance 1 -Pawn MeleeDPS -X 0 -Y 0 -Tries 30 | Select-Object -Last 1
for ($i = 0; $i -lt 10; $i++) { & "$H\ctl.ps1" -Action hold -Keys "44,100" | Out-Null; & "$H\ctl.ps1" -Action hold -Keys "41,100" | Out-Null; Start-Sleep 4 }
& "$H\ctl.ps1" -Action shot -Out "$env:TEMP\claude\retake-1.png" | Out-Null
foreach ($f in (Get-ChildItem "$H\..\..\build\run\be1v1-*.log" | Sort-Object LastWriteTime | Select-Object -Last 2)) { "== $($f.Name)"; Get-Content $f.FullName | Select-String 'teams: point' | Select-Object -Last 6 }
