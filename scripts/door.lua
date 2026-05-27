
local player = {}

function player:BehaviorLoop()
    while true do
        if playerID == nil then return end

        local deltaTime = coroutine.yield() --works well but not sure when you might want to pass other things

        local px, py = GetComponent(self.ID, "Position")

        local ex, ey = GetComponent(playerID, "Position")
        local dist = math.sqrt((ex - px) * (ex - px) + (ey - py) * (ey - py))

        if dist < 60 and PlayerHasKey == 0 then 
            RemoveEntity(self.ID)
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