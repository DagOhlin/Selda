print(":)")

creatables = {
    ground = function(x, y) 
        local ent = CreateEntity()
        AddComponent(ent, "Sprite", "textures/ground.png")
        AddComponent(ent, "Position", x, y)
    end,


    wall = function(x, y)
        local ent = CreateEntity()
        AddComponent(ent, "Sprite", "textures/wall.png")
        AddComponent(ent, "Position", x, y)
    end,

    enemy = function()
        
    end,

    player = function()

    end,

    button = function(x, y, func, text, width, height, color, scale)
        button = CreateEntity()

        local function func()
            print("Hello there")
        end

        text = text or ""
        width = width or 100
        height = height or 50
        color = color or {r = 0, g = 0, b = 255, a = 255}
        scale = scale or 1

        AddComponent(button, "Box", x, y, 200, 100)
        AddComponent(button, "Colour", 0, 0, 255, 255)
        AddComponent(button, "Text", text, 0, 0, 60, color.r, color.g, color.b, color.a)
        AddComponent(button, "Scale", scale)
        AddComponent(button, "Clickable", func)

        return button
    end
}

return creatables
