-- Included functions: 
-- int CreateEntity()
-- AddComponent(entity, string Component, args...)


print("hello")
-- local success, creatables = pcall(dofile, "scripts/creations.lua")
-- if not success then
--     print("Error loading creations.lua: " .. creatables)
--     return
-- end

print("Calling Init function")

local success, loadscene = pcall(dofile, "scripts/loadScene.lua")
print(success, loadscene)
if not success then
    print("Error loading creations.lua: " .. creatables)
    return
end

loadscene:LoadScene()