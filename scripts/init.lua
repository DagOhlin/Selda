-- Included functions: 
-- int CreateEntity()
-- AddComponent(entity, string Component, args...)


print("hello")
local success, creatables = pcall(dofile, "scripts/creations.lua")
if not success then
    print("Error loading creations.lua: " .. creatables)
    return
end

print("Calling Init function")


function SuperDuperFunc()  
    print("Hello there")
end

creatables.button(100, 100, SuperDuperFunc)
creatables.button(400, 100, SuperDuperFunc)
