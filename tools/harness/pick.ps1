param([int]$Instance = 1, [string]$Hero = 'Ninja')
# Picks a hero for the local player of an instance, then confirms the super and presses FIGHT (Space x2, posted keys).
$H = $PSScriptRoot
$dir = if ($Instance -eq 1) { 'ue4ss' } else { "ue4ss$Instance" }
& "$H\lua.ps1" -Dir $dir -Code "for _,pc in pairs(live(all('MBPlayerController'))) do if call(pc,'IsLocalController') == true then call(pc,'SelectCharacterOnServer', FName('$Hero')) plog('picked $Hero') end end" | Select-String 'picked'
Start-Sleep 2
& "$H\ctl.ps1" -Action post -Instance $Instance -Keys '20,20' | Out-Null
