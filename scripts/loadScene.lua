-- Included functions: 
-- int CreateEntity()
-- AddComponent(entity, string Component, args...)
local success, creatables = pcall(dofile, "scripts/creations.lua")
if not success then
    print("Error loading creations.lua: " .. creatables)
    return
end


function split(inputstr, sep) 
    sep=sep or '%s' local t={}  
    for field,s in string.gmatch(inputstr, "([^"..sep.."]*)("..sep.."?)") do 
        table.insert(t,field)  
        if s=="" then return t 
        end 
    end 
end

LoadScene = {}

function LoadScene:LoadScene()
    local lines = {}
    if f then 
        for line in io.lines("main.scene") do
            for id in split(line, "|") do
                
            end
        end
    end

    return lines


end

return LoadScene