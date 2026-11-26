-- Reflection helpers: pinfo(prop), dumpstruct(ustruct), fns(obj, stopClassName), children(fullNameSubstring)
function _G.pinfo(p)
    local t = p:GetClass():GetFName():ToString()
    local extra = ""
    if t == "StructProperty" then extra = p:GetStruct():GetFName():ToString()
    elseif t == "ArrayProperty" then
        local i = p:GetInner(); extra = i:GetClass():GetFName():ToString()
        if extra == "StructProperty" then extra = extra .. ":" .. i:GetStruct():GetFName():ToString()
        elseif extra == "ObjectProperty" then extra = extra .. ":" .. i:GetPropertyClass():GetFName():ToString() end
    elseif t == "ObjectProperty" or t == "ClassProperty" then pcall(function() extra = p:GetPropertyClass():GetFName():ToString() end)
    elseif t == "EnumProperty" or t == "ByteProperty" then pcall(function() extra = p:GetEnum():GetFName():ToString() end) end
    return string.format("%04x %-18s %s %s", p:GetOffset_Internal(), t, p:GetFName():ToString(), extra)
end
function _G.dumpstruct(s, depth)
    depth = depth or 0
    plog(string.rep("  ", depth) .. "struct " .. s:GetFName():ToString())
    s:ForEachProperty(function(p) plog(string.rep("  ", depth + 1) .. pinfo(p)) end)
end
function _G.fns(o, stop)
    local c = o:GetClass()
    while c and c:IsValid() do
        local names = {}
        c:ForEachFunction(function(f) names[#names + 1] = f:GetFName():ToString() end)
        plog(c:GetFName():ToString(), table.concat(names, " "))
        c = c:GetSuperStruct()
        if not c:IsValid() or c:GetFName():ToString() == (stop or "UserWidget") then break end
    end
end
function _G.props(o, stop)
    local c = o:GetClass()
    while c and c:IsValid() do
        c:ForEachProperty(function(p) plog(c:GetFName():ToString(), pinfo(p)) end)
        c = c:GetSuperStruct()
        if not c:IsValid() or c:GetFName():ToString() == (stop or "UserWidget") then break end
    end
end
function _G.children(sub)
    for _, w in pairs(live(all("Widget"))) do
        local f = fname(w)
        if f:find(sub, 1, true) then plog("child", cls(w):match("[^%.]+$"), f:match("[^%.]+$"), "vis", tostr(call(w, "GetVisibility"))) end
    end
end


-- The on-screen Custom Game screen (closed copies linger until GC; live ones have a parent slot).
function _G.cgscreen()
    for _, s in pairs(live(all("CustomGameScreen_C"))) do
        if fname(s):find("Transient", 1, true) and ok(call(s, "GetParent")) then return s end
    end
end
function _G.cgpress(what)
    local ev = {
        start = "BndEvt__FE_CustomGameMenu_K2Node_ComponentBoundEvent_47_OnStartGamePressed__DelegateSignature",
        settings = "BndEvt__FE_CustomGameMenu_K2Node_ComponentBoundEvent_16_OnSettingsPressed__DelegateSignature",
        maps = "BndEvt__FE_CustomGameMenu_K2Node_ComponentBoundEvent_12_OnMapsModesPressed__DelegateSignature",
        invite = "BndEvt__FE_CustomGameMenu_K2Node_ComponentBoundEvent_2_OnInviteFriendPressed__DelegateSignature",
        leave = "BndEvt__FE_CustomGameMenu_K2Node_ComponentBoundEvent_55_OnLeaveGamePressed__DelegateSignature",
    }
    local s = cgscreen()
    if not s then plog("no custom game screen") return end
    call(s, ev[what])
    plog("pressed " .. what)
end

-- Widgets of a class inside the on-screen Custom Game screen.
function _G.inscreen(clsname)
    local s = cgscreen()
    local out = {}
    if not s then return out end
    local sn = fname(s):match("[^%.]+$") .. "."
    for _, w in pairs(live(all(clsname))) do
        if fname(w):find(sn, 1, true) then out[#out + 1] = w end
    end
    return out
end
