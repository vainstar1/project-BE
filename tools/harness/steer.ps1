param([int]$Instance = 1, [double]$X, [double]$Y, [int]$Tries = 25, [double]$Near = 150, [string]$Pawn = '')
# Walks this instance's own character to (X, Y) with posted W/A/S/D. The camera doesn't turn without a mouse, so the
# keys move along fixed world axes; which key moves which way is measured on the first steps.
$H = $PSScriptRoot
$dir = if ($Instance -eq 1) { 'ue4ss' } else { "ue4ss$Instance" }
function Get-Pos {
    $code = 'for _, p in ipairs(live(all("MBProxyPawn"))) do if fname(p):find("PAWNNAME", 1, true) then local l = call(p, "K2_GetActorLocation") plog(string.format("POS %.0f %.0f", l.X, l.Y)) end end'.Replace('PAWNNAME', $Pawn)
    $r = & "$H\lua.ps1" -Dir $dir -Code $code | Select-String 'POS ' | Select-Object -Last 1
    if ("$r" -match 'POS (-?\d+) (-?\d+)') { return @([double]$matches[1], [double]$matches[2]) }
    return $null
}
$keys = @{ '57' = @(0, -1); '53' = @(0, 1); '41' = @(-1, 0); '44' = @(1, 0) }   # assumed W -Y, S +Y, A -X, D +X
for ($i = 0; $i -lt $Tries; $i++) {
    $p = Get-Pos
    if (-not $p) { "no position"; return }
    $dx = $X - $p[0]; $dy = $Y - $p[1]
    if ([math]::Sqrt($dx * $dx + $dy * $dy) -lt $Near) { "arrived at $($p[0]) $($p[1])"; return }
    if ([math]::Abs($dx) -gt [math]::Abs($dy)) { $k = if ($dx -gt 0) { '44' } else { '41' }; $d = [math]::Abs($dx) }
    else { $k = if ($dy -gt 0) { '53' } else { '57' }; $d = [math]::Abs($dy) }
    $ms = [int][math]::Min(1500, [math]::Max(150, $d / 1.2))
    & "$H\ctl.ps1" -Action hold -Instance $Instance -Keys "$k,$ms" | Out-Null
}
$p = Get-Pos
"stopped at $($p[0]) $($p[1])"
