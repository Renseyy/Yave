--- MAIN.LUA
local fun = on("init", function(e)
    print(e)
    local textureManager = e.getTextureManager();
    print(textureManager.addTexture)
    textureManager.addTexture("textures/dirt.png")
end)
