print(":)")

creatables = {
    ground = function(x, y) 
        local ent = CreateEntity()
        AddComponent(ent, "Sprite", "textures/Ground.png")
        AddComponent(ent, "Position", x, y)
        AddComponent(ent, "Box", x, y, 16, 16)
        -- AddComponent(ent, "TypeName", "Ground")
        return ent
    end,
    
    
    wall = function(x, y)
        local ent = CreateEntity()
        AddComponent(ent, "Sprite", "textures/Wall.png")
        AddComponent(ent, "Position", x, y)
        AddComponent(ent, "Box", x, y, 16, 16)
        AddComponent(ent, "BoxCollider", 16, 16, 0, 0, true);
        print(x * 16, y * 16)
        -- AddComponent(ent, "TypeName", "Wall")

        return ent
    end,

    enemy = function()
        
        -- AddComponent(ent, "TypeName", "Enemy")
    end,

    player = function(x, y)
        local ent = CreateEntity()
        AddComponent(ent, "Sprite", "textures/Blink2.png")
        AddComponent(ent, "Position", x, y)
        AddComponent(ent, "CharacterController", 100.0);
        AddComponent(ent, "Velocity", 50.0, 0.0, 0.0);
        AddComponent(ent, "BoxCollider", 6 , 16 , (16 - 6) / 2, 0, true);
        AddComponent(ent, "luaBehaviour", "./scripts/behaviorTest.lua")
        -- AddComponent(ent, "TypeName", "Player")
        return ent
    end,

    button = function(x, y, func, text, width, height, color, scale)
        local button = CreateEntity()

        local text = text or ""
        local width = width or 100
        local height = height or 50
        local color = color or {r = 0, g = 0, b = 255, a = 255}
        local scale = scale or 1

        -- AddComponent(button, "TypeName", "Button")
        AddComponent(button, "Box", x, y, 200, 100)
        AddComponent(button, "Colour", 40, 40, 40, 255)
        AddComponent(button, "Text", text, 0, 0, 60, color.r, color.g, color.b, color.a)
        AddComponent(button, "Scale", scale)
        AddComponent(button, "Clickable", func)

        return button
    end
}

return creatables
