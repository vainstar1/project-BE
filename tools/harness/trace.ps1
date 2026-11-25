param([int]$Instance = 1, [Parameter(Mandatory = $true)][string]$Agent, [int]$Seconds = 40, [string]$Out = "$env:TEMP\bere\trace$Instance.txt")
# Starts a background Frida trace of a game instance. Agent paths are relative to tools\re\frida.
$node = 'C:\Users\andre\OneDrive\Desktop\big folder\bleeding-edge-rea-research\tools\node-v22.19.0-win-x64\node.exe'
$re = Join-Path $PSScriptRoot '..\re\frida' | Resolve-Path
$name = if ($Instance -eq 1) { 'MobladeClient-Win64-Shipping' } else { "BEInstance$Instance-Win64-Shipping" }
$p = Get-Process -Name $name -ErrorAction Stop | Select-Object -First 1
New-Item -ItemType Directory -Force (Split-Path $Out) | Out-Null
Start-Process -FilePath $node -ArgumentList "`"$re\attach.js`" $($p.Id) `"$re\$Agent`" $Seconds" -RedirectStandardOutput $Out -RedirectStandardError "$Out.err" -WindowStyle Hidden
$deadline = (Get-Date).AddSeconds(20)
while ((Get-Date) -lt $deadline) { Start-Sleep -Milliseconds 300; if ((Test-Path $Out) -and (Select-String -Path $Out -Pattern 'agent loaded' -Quiet)) { "trace running -> $Out"; return } }
"trace did not start"; Get-Content "$Out.err" -ErrorAction SilentlyContinue
