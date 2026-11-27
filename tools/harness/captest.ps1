param([int]$T2 = 2, [string]$Rules = '50,0,0,1,0,0,0,3,0,0', [int]$Seconds = 200)
# 3-team Objective Control: instance 2 (Cass, team T2) walks to the centre capture point of Train and waits for it
# to become active (rotation), stepping a little so the idle kick doesn't fire. 50 points to win: one capture wins.
$H = $PSScriptRoot
$env:BE_RES = '1280x720'
& "$H\teamtest.ps1" -T1 0 -T2 $T2 -Rules $Rules | Select-Object -Last 1
& "$H\waitstate.ps1"
& "$H\dev.ps1" -Cmd noafk | Out-Null
& "$H\dev.ps1" -Instance 2 -Cmd noafk | Out-Null
& "$H\ctl.ps1" -Action hold -Instance 2 -Keys "44,1200" | Out-Null
& "$H\ctl.ps1" -Action hold -Instance 2 -Keys "57,2500" | Out-Null
& "$H\steer.ps1" -Instance 2 -Pawn Cass -X 0 -Y 0 -Tries 30 | Select-Object -Last 1
$end = (Get-Date).AddSeconds($Seconds)
$logs = Get-ChildItem "$H\..\..\build\run\be1v1-*.log" | Sort-Object LastWriteTime | Select-Object -Last 2
while ((Get-Date) -lt $end) {
    & "$H\ctl.ps1" -Action hold -Instance 2 -Keys "44,100" | Out-Null
    & "$H\ctl.ps1" -Action hold -Instance 2 -Keys "41,100" | Out-Null
    Start-Sleep 6
    if ($logs | ForEach-Object { Get-Content $_.FullName } | Select-String 'wins with') { break }
}
& "$H\ctl.ps1" -Action shot -Instance 2 -Out "$env:TEMP\claude\cap-2.png" | Out-Null
& "$H\ctl.ps1" -Action shot -Out "$env:TEMP\claude\cap-1.png" | Out-Null
foreach ($f in $logs) { "== $($f.Name)"; Get-Content $f.FullName | Select-String 'teams: (point|team \d wins|match result)' | Select-Object -Last 8 }
