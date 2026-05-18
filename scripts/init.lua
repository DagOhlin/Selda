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

function Play(entity) 
    ClearScene()
    loadscene:LoadScene(false)
end

function Editor(entity)
    ClearScene()
    loadscene:LoadScene(true)
end


button1 = creatables.button(100, 100, Play, "Play")
button2 = creatables.button(100, 200, Play, "Editor")
button3 = creatables.button(100, 300, Quit, "Quit")
button4 = creatables.button(100, 400, Editor, "Play")
