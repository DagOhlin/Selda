print(":)")

playerID = nil
enemies = {}
bosses = {}

creatables = {
    ground = function(x, y) 
        local ent = CreateEntity()
        AddComponent(ent, "Sprite", "textures/Ground.png", 0)
        AddComponent(ent, "Position", x, y)
        AddComponent(ent, "Box", x, y, 16, 16)
        -- AddComponent(ent, "TypeName", "Ground")
        return ent
    end,
    
    
    wall = function(x, y)
        local ent = CreateEntity()
        AddComponent(ent, "Sprite", "textures/Wall.png", 0)
        AddComponent(ent, "Position", x, y)
        AddComponent(ent, "Box", x, y, 16, 16)
        AddComponent(ent, "BoxCollider", 16, 16, 0, 0, true);
        -- AddComponent(ent, "TypeName", "Wall")
        
        return ent
    end,

    chest = function(x, y)
        local ent = CreateEntity()
        AddComponent(ent, "Sprite", "textures/Chest.png", 1)
        AddComponent(ent, "Position", x, y)
        AddComponent(ent, "LuaBehaviour", "./scripts/chest.lua")
        -- AddComponent(ent, "TypeName", "Wall")
        
        return ent
    end,
    key = function(x, y)
        local ent = CreateEntity()
        AddComponent(ent, "Sprite", "textures/Key.png", 1)
        AddComponent(ent, "Position", x, y)
        AddComponent(ent, "LuaBehaviour", "./scripts/key.lua")
        -- AddComponent(ent, "TypeName", "Wall")
        
        return ent
    end,

    door = function(x, y)
        local ent = CreateEntity()
        AddComponent(ent, "Sprite", "textures/Door.png", 1)
        AddComponent(ent, "Position", x, y)
        AddComponent(ent, "Box", x, y, 16, 16)
        AddComponent(ent, "BoxCollider", 16, 16, 0, 0, true);
        AddComponent(ent, "LuaBehaviour", "./scripts/door.lua")
        -- AddComponent(ent, "TypeName", "Wall")
        
        return ent
    end,
    
    enemy = function(x, y)
        local ent = CreateEntity()
        AddComponent(ent, "BoxCollider", 16, 16, 0, 0, true);
        AddComponent(ent, "Sprite", "textures/Enemy.png", 1)
        AddComponent(ent, "Position", x, y)
        AddComponent(ent, "LuaBehaviour", "./scripts/enemy.lua")
        AddComponent(ent, "Health", 5)
        table.insert(enemies, ent)

        return ent
    end,

    boss = function(x, y)
        local ent = CreateEntity()
        AddComponent(ent, "BoxCollider", 16, 16, 0, 0, true);
        AddComponent(ent, "Sprite", "textures/Boss.png", 1)
        AddComponent(ent, "Position", x, y)
        AddComponent(ent, "LuaBehaviour", "./scripts/boss.lua")
        AddComponent(ent, "Health", 1)
        table.insert(bosses, ent)

        return ent
    end,

    text = function (x, y, text, width, height, color)
        local width = width or 100
        local height = height or 50
        local color = color or {r = 0, g = 0, b = 255, a = 255}

        local ent = CreateEntity()
        AddComponent(ent, "Box", x, y, width, height)
        AddComponent(ent, "Text", text, 0, 0, 60, color.r, color.g, color.b, color.a)

        return ent
    end,

    player = function(x, y)
        local ent = CreateEntity()
        playerID = ent
        AddComponent(ent, "Sprite", "textures/Blink2.png", 1)
        AddComponent(ent, "Position", x, y)
        AddComponent(ent, "CharacterController", 800.0);
        AddComponent(ent, "Velocity", 50.0, 0.0, 0.0);
        AddComponent(ent, "BoxCollider", 7 , 12 , 4.5, 3, true);
        AddComponent(ent, "LuaBehaviour", "./scripts/player.lua")
        AddComponent(ent, "Health", 20)

        -- AddComponent(ent, "TypeName", "Player")
        return ent
    end,

    button = function(x, y, func, text, width, height, color, scale)
        local button = CreateEntity()

        local text = text or ""
        local width = width or 200
        local height = height or 100
        local color = color or {r = 0, g = 0, b = 255, a = 255}
        local scale = scale or 1

        -- AddComponent(button, "TypeName", "Button")
        AddComponent(button, "Box", x, y, width, height)
        AddComponent(button, "Text", text, 0, 0, 60, color.r, color.g, color.b, color.a)
        AddComponent(button, "Colour", 40, 40, 40, 255)
        AddComponent(button, "Scale", scale)
        AddComponent(button, "Clickable", func)

        return button
    end

    


    -- ,

    -- killMonster = function(monsterID)
    --     table.remove(monsterID)
    --     RemoveEntity(monsterID)

    -- end
}

return creatables
