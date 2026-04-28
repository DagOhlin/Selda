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
AddComponent(button);
AddComponent(button);

AddComponent(button, "Clickable", "SuperDuperFunc", SuperDuperFunc);
