param([int]$T1 = 0, [int]$T2 = 2, [string]$Rules = '0,0,0,4,2,0,1,4,1,1', [switch]$NoBoot)
# Team Brawl knockout test on Train: instance 1 (Daemon, team T1) and instance 2 (Cass, team T2) spawn in base A (teams
# 0 and 2 share it), walk out through the spawn door, meet, and Daemon uses its super on Cass (Super Powered map mod).
$H = $PSScriptRoot
$env:BE_RES = '1280x720'
& "$H\teamtest.ps1" -T1 $T1 -T2 $T2 -Rules $Rules -NoBoot:$NoBoot | Select-Object -Last 1
& "$H\dev.ps1" -Cmd testbinds | Out-Null
& "$H\dev.ps1" -Instance 2 -Cmd testbinds | Out-Null
& "$H\waitstate.ps1"
& "$H\ctl.ps1" -Action hold -Instance 2 -Keys "44,1200" | Out-Null
& "$H\ctl.ps1" -Action hold -Instance 2 -Keys "57,2500" | Out-Null
& "$H\ctl.ps1" -Action hold -Keys "41,450" | Out-Null
& "$H\ctl.ps1" -Action hold -Keys "57,2500" | Out-Null
& "$H\ctl.ps1" -Action hold -Keys "44,250" | Out-Null
& "$H\pos.ps1"
& "$H\ctl.ps1" -Action hold -Keys "41,100" | Out-Null
& "$H\ctl.ps1" -Action post -Keys "52" | Out-Null
Start-Sleep 1
& "$H\ctl.ps1" -Action post -Keys "52" | Out-Null
Start-Sleep 4
& "$H\pos.ps1"
# The super charges in about a minute with Super Powered: face the other player (behind/ahead) and use it.
Start-Sleep 30
foreach ($turn in '53', '57', '41', '44') {
    & "$H\ctl.ps1" -Action hold -Keys "$turn,120" | Out-Null
    & "$H\ctl.ps1" -Action post -Keys "52" | Out-Null
    Start-Sleep 4
    $ended = Get-Content (Get-ChildItem "$H\..\..\build\run\be1v1-*.log" | Sort-Object LastWriteTime | Select-Object -Last 1).FullName | Select-String 'wins with'
    if ($ended) { break }
}
Start-Sleep 3
$S = "$env:TEMP\claude\ko"
& "$H\ctl.ps1" -Action shot -Out "$S-1.png" | Out-Null
& "$H\ctl.ps1" -Action shot -Instance 2 -Out "$S-2.png" | Out-Null
foreach ($f in (Get-ChildItem "$H\..\..\build\run\be1v1-*.log" | Sort-Object LastWriteTime | Select-Object -Last 2)) { "== $($f.Name)"; Get-Content $f.FullName | Select-String 'teams: ' | Select-Object -Last 4 }
