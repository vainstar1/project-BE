param([string]$Code = '', [string]$File = '', [string]$Dir = "$PSScriptRoot\ue4ss", [int]$Timeout = 60)
# Sends Lua to the BEProbe command channel and prints the log lines it produced.
if ($File) { $Code = Get-Content -Raw $File }
# Reload the shared helper library on every call so edits take effect without restarting the game.
$Code = "dofile([[$PSScriptRoot\helpers.lua]])`n" + $Code
if (-not [IO.Path]::IsPathRooted($Dir)) { $Dir = Join-Path $PSScriptRoot $Dir }
$log = Join-Path $Dir 'probe.log'
$start = if (Test-Path $log) { (Get-Item $log).Length } else { 0 }
[IO.File]::WriteAllText((Join-Path $Dir 'cmd.txt'), $Code)
$deadline = (Get-Date).AddSeconds($Timeout)
while ((Get-Date) -lt $deadline) {
    Start-Sleep -Milliseconds 300
    if (-not (Test-Path $log)) { continue }
    $fs = [IO.File]::Open($log, 'Open', 'Read', 'ReadWrite')
    $fs.Seek($start, 'Begin') | Out-Null
    $txt = (New-Object IO.StreamReader($fs)).ReadToEnd(); $fs.Close()
    if ($txt -match '<<< done') { $txt; return }
}
"TIMEOUT"; if ($txt) { $txt }
