#version 460 core 
out vec4 FragColor;

in vec3 ourColor; //output from base.vertex

void main()
{
    FragColor = vec4(ourColor, 1.0f);
}