-- Included functions: 
-- int CreateEntity()
-- AddComponent(entity, string Component, args...)
local success, creatables = pcall(dofile, "scripts/creations.lua")
if not success then
    print("Error loading creations.lua: " .. creatables)
    return
end

function split(inputstr, sep)
    sep = sep or "%s"
    local t = {}

    for field, s in string.gmatch(inputstr, "([^" .. sep .. "]+)(" .. sep .. "?)") do
        table.insert(t, field)
        if s == "" then
            return t
        end
    end

    return t
end

LoadScene = {}

function LoadScene:CreateEntities(x, y, block)
    for _, object in ipairs(split(block, ":")) do
        local scale = 4
        local x, y = x * scale, y * scale

        if (object == "Wall") then
            entity = creatables.wall(x, y)
        elseif (object == "Ground") then
            entity = creatables.ground(x, y)
        elseif (object == "Enemy") then
            entity = creatables.enemy(x, y)
        elseif (object == "Player") then
            entity = creatables.player(x, y)
        end

        AddComponent(entity, "Scale", scale)

    end
end

function LoadScene:CreateEditorEntities(x, y, block)
    for _, object in ipairs(split(block, ":")) do
        local entity = nil
        if (object == "Wall") then
            entity = creatables.wall(x, y)
        elseif (object == "Ground") then
            entity = creatables.ground(x, y)
        elseif (object == "Enemy") then
            entity = creatables.enemy(x, y)
        elseif (object == "Player") then
            entity = creatables.player(x, y)
        end
        
        AddComponent(entity, "TypeName", object)
    end
end

function LoadScene:LoadScene(editor)
    local y = 1
    for line in io.lines("scenes/main.simon") do
        for x, block in pairs(split(line, "|"))  do
            if editor then
                LoadScene:CreateEditorEntities(x * 16, y * 16, block)
            else 
                LoadScene:CreateEntities(x * 16, y * 16, block)
            end
        end
        y = y + 1
    end
    
    if editor then
        local ent = creatables.wall(0, y * 16)
        AddComponent(ent, "TypeName", "Wall")
        AddComponent(ent, "Selector")

        ent = creatables.ground(16, y * 16)
        AddComponent(ent, "TypeName", "Ground")
        AddComponent(ent, "Selector")
        
        ent = creatables.enemy(16 * 2, y * 16)
        AddComponent(ent, "TypeName", "Enemy")
        RemoveComponent(ent, "LuaBehaviour")
        AddComponent(ent, "Selector")
        AddComponent(ent, "Box", 16 * 2, y * 16, 16, 16)

        -- ent = creatables.ground(16, y * 16)
        -- AddComponent(ent, "TypeName", "Ground")
        -- AddComponent(ent, "Selector")
        local button = creatables.button(64, y * 16, Save, "Save")

    end
end

return LoadScene