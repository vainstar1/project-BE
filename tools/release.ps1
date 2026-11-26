param([string]$Notes = '', [switch]$Draft, [switch]$NoBuild)
# Builds the mod, packages dist\BE1v1.zip and publishes it as a GitHub release of vainstar1/project-BE.
# The tag is "v" + BE1V1_VERSION from host\src\mod.h. The installed mod checks this repo's latest release at start-up
# and offers to update when the tag is newer than its own version.
# The GitHub token comes from git's credential store (the same one git push uses); it is never written to disk.
$ErrorActionPreference = 'Stop'
$root = Split-Path $PSScriptRoot -Parent
$repo = 'vainstar1/project-BE'
$ver = (Select-String -Path "$root\host\src\mod.h" -Pattern '#define BE1V1_VERSION "([^"]+)"').Matches[0].Groups[1].Value
$tag = "v$ver"
# Git for Windows' bash runs the build and reads the credential (its login shell has the tools on PATH).
$bash = 'C:\Program Files\Git\bin\bash.exe'
$unixRoot = (& $bash -lc "cygpath -u '$root'").Trim()
if (-not $NoBuild) { & $bash -lc "cd '$unixRoot' && sh tools/package.sh" | Select-Object -Last 3 }
$zip = "$root\dist\BE1v1.zip"
if (-not (Test-Path $zip)) { throw "missing $zip" }

$cred = & $bash -lc "printf 'protocol=https\nhost=github.com\n\n' | git credential fill"
$token = ($cred | Where-Object { $_ -like 'password=*' }) -replace '^password=', ''
if (-not $token) { throw 'no GitHub credential found' }
$h = @{ Authorization = "token $token"; Accept = 'application/vnd.github+json'; 'User-Agent' = 'BE1v1-release' }

$existing = $null
try { $existing = Invoke-RestMethod -Headers $h "https://api.github.com/repos/$repo/releases/tags/$tag" } catch {}
if ($existing) {
    "release $tag exists (id $($existing.id)); replacing its zip"
    foreach ($a in $existing.assets) { if ($a.name -eq 'BE1v1.zip') { Invoke-RestMethod -Method Delete -Headers $h $a.url | Out-Null } }
    $rel = $existing
} else {
    if (-not $Notes) { $Notes = "BE1v1 $ver" }
    $body = @{ tag_name = $tag; name = "BE1v1 $ver"; body = $Notes; draft = [bool]$Draft; target_commitish = 'main' } | ConvertTo-Json
    $rel = Invoke-RestMethod -Method Post -Headers $h -Body $body -ContentType 'application/json' "https://api.github.com/repos/$repo/releases"
    "created release $tag (id $($rel.id))"
}
$upload = $rel.upload_url -replace '\{.*\}$', ''
$asset = Invoke-RestMethod -Method Post -Headers $h -ContentType 'application/zip' -InFile $zip "$($upload)?name=BE1v1.zip"
"uploaded $($asset.name) ($($asset.size) bytes) -> $($asset.browser_download_url)"
