
local monster = {}
monster.lifespan = 3.0

function monster:BehaviorLoop()
    while self.lifespan > 0 do
        
        local deltaTime = coroutine.yield() --works well but not sure when you might want to pass other things
        
        self.lifespan = self.lifespan - deltaTime
        -- print("Monster dancing, ID:", self.ID, "time to live:", self.lifespan)
        
    end
    
    print("Monster dead, ID:", self.ID)
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