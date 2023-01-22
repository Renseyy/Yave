#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float addon;

void main()
{
    float tmp = (addon - 0.5f);
    float tmpY = aPos.y + 0.5f;
    gl_Position = projection * view  * model* vec4(aPos.x + tmp * tmpY ,aPos.y, aPos.z + tmp * tmpY, 1.0f);
    TexCoord = aTexCoord;
}