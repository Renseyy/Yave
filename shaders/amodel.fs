//fragment shader for animations
// ! remember when updating to update also internal shaders in src/shaders.cpp

#version 400 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{    
    FragColor = texture(texture_diffuse1, TexCoords);
}