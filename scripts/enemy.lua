
local monster = {}
monster.lifespan = 3.0

function monster:BehaviorLoop()
    local lastHit = 0
    local timer = 0
    local hitCooldown = 1

    while true do
        
        local deltaTime = coroutine.yield() --works well but not sure when you might want to pass other things
        timer = timer + deltaTime
        local px, py = GetComponent(playerID, "Position");
        local mx, my = GetComponent(self.ID, "Position")
        local monsterSpeed = 2000 * deltaTime

        local dirx, diry  = px - mx, py - my

        dist = math.sqrt(dirx * dirx + diry * diry)

        if dist < 20 and lastHit + hitCooldown < timer then
            lastHit = timer
            playerHealth = GetComponent(playerID, "Health")
            playerHealth = playerHealth - 1
            if playerHealth <= 0 then
                Quit()
            end

            AddComponent(healthText, "Text", "Health: " .. playerHealth, 0, 0, 60, 0, 0, 255, 255)
            AddComponent(playerID, "Health", playerHealth)
        end
        
        AddComponent(self.ID, "Velocity", 10000, dirx * monsterSpeed / dist, diry * monsterSpeed / dist)
    end
end

-- remeber to allways use onCreate exactly, C++ is looking by name
function monster:OnCreate()
    print("Monster created ID:", self.ID)
    
    self.co = coroutine.create(function() self:BehaviorLoop() end)
end


function monster:OnUpdate(delta)
    if coroutine.status(self.co) ~= "dead" then --dead is a great thing to call it
        
        local success, err = coroutine.resume(self.co, delta)
        
        if not success then
            print("Error in coroutine:", err)
        end
    end
end

return monster