
local player = {}

function player:BehaviorLoop()
    local lastHit = 0
    local timer = 0
    local hitCooldown = 1

    local swordEntity = nil
    local swordDespawnTime = 0
    local didHit = false

    while true do
        
        local deltaTime = coroutine.yield() --works well but not sure when you might want to pass other things
        timer = timer + deltaTime
        
        if swordEntity ~= nil and timer >= swordDespawnTime then
            RemoveEntity(swordEntity)
            swordEntity = nil
        end

        if swordEntity ~= nil then
            
            AddComponent(swordEntity, "Position", px, py)
        end

        px, py = GetComponent(self.ID, "Position")

        if IsPressed(" ") and (lastHit + hitCooldown) < timer then
            lastHit = timer
            didHit = false
            

            for index, monster in ipairs(enemies) do
                ex, ey = GetComponent(monster, "Position")
                dist = math.sqrt((ex - px) * (ex - px) + (ey - py) * (ey - py))

                if dist < 40 then 
                    didHit = true
                    monsterHealth = GetComponent(monster, "Health")
                    monsterHealth = monsterHealth - 1
                    if monsterHealth <= 0 then
                        table.remove(enemies, index)
                        RemoveEntity(monster)
                    else
                        AddComponent(monster, "Health", monsterHealth)
                    end

                end
            end

            swordEntity = CreateEntity()
            
            if (didHit == true) then
                AddComponent(swordEntity, "Sprite", "textures/bloodSword.png", 2)
            else
                AddComponent(swordEntity, "Sprite", "textures/sword.png", 2)
            end
            AddComponent(swordEntity, "Scale", 4)
            AddComponent(swordEntity, "Position", px, py)
            
            swordDespawnTime = timer + 0.25
        end
        
    end
end

-- remeber to allways use onCreate exactly, C++ is looking by name
function player:OnCreate()
    self.co = coroutine.create(function() self:BehaviorLoop() end)
end


function player:OnUpdate(delta)
    if coroutine.status(self.co) ~= "dead" then --dead is a great thing to call it
        
        local success, err = coroutine.resume(self.co, delta)
        
        if not success then
            print("Error in coroutine:", err)
        end
    end
end

return player