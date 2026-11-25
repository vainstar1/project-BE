param([Parameter(Mandatory = $true)][string]$Cmd, [int]$Instance = 1)
# Sends a developer command to be1v1.dll in a running instance (polled twice a second on the game thread).
$name = if ($Instance -eq 1) { 'MobladeClient-Win64-Shipping' } else { "BEInstance$Instance-Win64-Shipping" }
$p = Get-Process -Name $name -ErrorAction Stop | Select-Object -First 1
$run = Join-Path $PSScriptRoot '..\..\build\run'
[IO.File]::WriteAllText((Join-Path $run "be1v1-cmd-$($p.Id).txt"), $Cmd)
Start-Sleep -Milliseconds 700
Get-Content (Join-Path $run "be1v1-$($p.Id).log") -Tail 8
