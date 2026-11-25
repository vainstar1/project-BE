param([int]$Instance = 1, [string]$ExtraArgs = '', [switch]$NoBoot)
# Boots an instance (unless -NoBoot) and gets it past the title screen to the main menu.
$H = $PSScriptRoot
$dir = if ($Instance -eq 1) { 'ue4ss' } else { "ue4ss$Instance" }
if (-not $NoBoot) {
    & "$H\ctl.ps1" -Action kill -Instance $Instance | Out-Null
    Start-Sleep 1
    & "$H\ctl.ps1" -Action boot -Instance $Instance -ExtraArgs $ExtraArgs
}
$deadline = (Get-Date).AddSeconds(90)
while ((Get-Date) -lt $deadline) {
    $r = & "$H\lua.ps1" -Dir $dir -Code @'
local s = live(all("FE_StartScreen_C"))[1]
local m = live(all("FE_MainMenuScreen_C"))[1]
if s and call(s, "IsVisible") == true then call(s, "BndEvt__PressStart_K2Node_ComponentBoundEvent_3_StartPressed__DelegateSignature") plog("STATE start") return end
if m and call(m, "IsVisible") == true then plog("STATE menu") return end
plog("STATE wait")
'@
    if ($r -match 'STATE menu') { "main menu ready"; return }
    Start-Sleep 4
}
"main menu timeout"
