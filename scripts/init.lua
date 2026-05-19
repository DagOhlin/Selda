-- Included functions: 
-- int CreateEntity()
-- void AddComponent(int entity, string Component, T args...)
-- void ClearScene()
-- void Quit()


print("hello")
local success, creatables = pcall(dofile, "scripts/creations.lua")
if not success then
    print("Error loading creations.lua: " .. creatables)
    return
end

local success, loadscene = pcall(dofile, "scripts/loadScene.lua")
print(success, loadscene)
if not success then
    print("Error loading creations.lua: " .. creatables)
    return
end

function g() 
    ClearScene()
    loadscene:LoadScene()
end

function f()
    Quit()
end


button = creatables.button(100, 100, g, "Play")
button = creatables.button(100, 200, Quit, "Quit")
