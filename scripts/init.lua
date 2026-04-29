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

player = CreateEntity();

AddComponent(player, "Position", 100.0, 100.0);
AddComponent(player, "Sprite", "textures/Blink2.png"); 
AddComponent(player, "Scale", 8.0);
AddComponent(player, "CharacterController", 30.0);
AddComponent(player, "Velocity", 50.0, 0.0, 0.0);
AddComponent(player, "BoxCollider", 144.0, 144.0, true);

obstacle = CreateEntity();

AddComponent(player, "Position", 300.0, 300.0);
AddComponent(player, "BoxCollider", 32.0, 32.0, true);
