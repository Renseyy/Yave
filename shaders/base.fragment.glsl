#version 400 core 

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D tex;
uniform vec4 color;
uniform bool texturing;
void main()
{
    if(texturing){
        FragColor = texture(tex, TexCoord) * color;
    }else{
        FragColor = color;
    }
}