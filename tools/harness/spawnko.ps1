# Inside the shared spawn room (teams 0 and 2, base A on Train): Daemon walks next to Cass and uses its super.
$H = $PSScriptRoot
$env:BE_RES = '1280x720'
& "$H\teamtest.ps1" -T1 0 -T2 2 -Rules '0,0,0,4,2,0,1,4,1' | Select-Object -Last 1
& "$H\dev.ps1" -Cmd testbinds | Out-Null
& "$H\dev.ps1" -Instance 2 -Cmd testbinds | Out-Null
& "$H\waitstate.ps1"
& "$H\ctl.ps1" -Action hold -Keys "41,1100" | Out-Null
& "$H\pos.ps1"
Start-Sleep 55
foreach ($turn in '41', '44', '53', '57', '41') {
    & "$H\pos.ps1"
    & "$H\ctl.ps1" -Action hold -Keys "$turn,100" | Out-Null
    & "$H\ctl.ps1" -Action post -Keys "52" | Out-Null
    Start-Sleep 5
}
& "$H\ctl.ps1" -Action shot -Instance 2 -Out "$env:TEMP\claude\spawnko-2.png" | Out-Null
foreach ($f in (Get-ChildItem "$H\..\..\build\run\be1v1-*.log" | Sort-Object LastWriteTime | Select-Object -Last 2)) { "== $($f.Name)"; Get-Content $f.FullName | Select-String 'teams: ' | Select-Object -Last 3 }
