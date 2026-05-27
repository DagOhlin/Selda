-- Included functions: 
-- int CreateEntity()
-- void AddComponent(int entity, string Component, T args...)
-- void ClearScene()
-- void Quit()

function ClearSceneSafe() 
    enemies = {}
    playerID = nil
    ClearScene()
end


print("hello")
local success, creatables = pcall(dofile, "scripts/creations.lua")
if not success then
    print("Error loading creations.lua: " .. creatables)
    return
end

local success, loadscene = pcall(dofile, "scripts/loadScene.lua")
if not success then
    print("Error loading creations.lua: " .. creatables)
    return
end

function Play(entity) 
    ClearSceneSafe()
    loadscene:LoadScene(false)
end

function Editor(entity)
    ClearSceneSafe()
    loadscene:LoadScene(true)
end

function MainMenu()
    ClearSceneSafe()
    local button1 = creatables.button(100, 100, Play, "Play")
    local button2 = creatables.button(100, 200, Editor, "Editor")
end

MainMenu()

