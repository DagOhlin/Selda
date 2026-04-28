-- Included functions: 
-- int CreateEntity()
-- AddComponent(entity, string Component, args...)


print("Calling Init function");

button = CreateEntity();

function SuperDuperFunc()  
    print("Hello there");
end

AddComponent(button, "Box", 300, 200, 200, 100);
AddComponent(button, "Colour", 0, 0, 255, 255);
AddComponent(button, "Text", "hello", 0, 0, 60, 255, 255, 78, 255);


blink = CreateEntity();

AddComponent(blink, "Position", 100.0, 100.0);
AddComponent(blink, "Sprite", "textures/Blink2.png"); 
AddComponent(blink, "Scale", 8.0);
AddComponent(blink, "CharacterController", 30.0);

AddComponent(button, "Clickable", "SuperDuperFunc", SuperDuperFunc);
