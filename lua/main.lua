--- MAIN.LUA
_init(function(e)

end)
on("init", function(e)
    local textureManager = e.getTextureManager();
    print(textureManager.addTexture)
    textureManager.addTexture("textures/dirt.png")

    
end)
