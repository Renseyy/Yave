#version 460 core 

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D tex;
uniform vec4 color;
void main()
{
    if(color.w > 0){
        FragColor = texture(tex, TexCoord) *  color;
    }else{
        FragColor = texture(tex, TexCoord);
    }
}