function Register()
    return "44 8B 05 ?? ?? ?? ?? 4C 8B 0D ?? ?? ?? ?? 8B 47 0C 41 3B C0 7D 21 99"
end

function OnMatchFound(matchAddress)
    local movInstr = matchAddress + 0x7
    local nextInstr = movInstr + 0x7
    local offset = movInstr + 0x3
    local objObjects = nextInstr + DerefToInt32(offset)
    return objObjects - 0x10
end
