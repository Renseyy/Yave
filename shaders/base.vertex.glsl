#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float addon;

void main()
{
    float tmp = (addon - 0.5f) * 2;
    float tmpY = aPos.y + 0.5f;
    gl_Position = projection * view  * vec4(aPos.x + tmp * tmpY ,aPos.y, 1.0f);
    ourColor = aColor;
}