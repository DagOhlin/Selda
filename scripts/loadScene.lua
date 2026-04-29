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
        if (object == "Wall") then
            creatables.wall(x, y) 
        elseif (object == "Ground") then
            creatables.ground(x, y)
        elseif (object == "Enemy") then
            creatables.enemy(x, y)
        end
    end
end

function LoadScene:LoadScene()
    local y = 1
    for line in io.lines("scenes/main.simon") do
        for x, block in pairs(split(line, "|"))  do
            LoadScene:CreateEntities(x * 16, y * 16, block)
        end
        y = y + 1
    end
end

return LoadScene