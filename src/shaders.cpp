const char *YAVE_VS_ANIM =
"#version 400 core\n"

"layout(location = 0) in vec3 pos;\n"
"layout(location = 1) in vec3 norm;\n"
"layout(location = 2) in vec2 tex;\n"
"layout(location = 3) in vec3 tangent;\n"
"layout(location = 4) in vec3 bitangent;\n"
"layout(location = 5) in ivec4 boneIds;\n" 
"layout(location = 6) in vec4 weights;\n"

"uniform mat4 projection;\n"
"uniform mat4 view;\n"
"uniform mat4 model;\n"

"const int MAX_BONES = 100;\n"
"const int MAX_BONE_INFLUENCE = 4;"
"uniform mat4 finalBonesMatrices[MAX_BONES];\n"

"out vec2 TexCoords;\n"

"void main()\n"
"{\n"
    "vec4 totalPosition = vec4(0.0f);\n"
    "for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)\n"
    "{\n"
        "if(boneIds[i] == -1) \n"
            "continue;\n"
        "if(boneIds[i] >=MAX_BONES) \n"
        "{\n"
            "totalPosition = vec4(pos,1.0f);\n"
            "break;\n"
        "}\n"
        "vec4 localPosition = finalBonesMatrices[boneIds[i]] * vec4(pos,1.0f);\n"
        "totalPosition += localPosition * weights[i];\n"
        "vec3 localNormal = mat3(finalBonesMatrices[boneIds[i]]) * norm;\n"
   "}\n"
	
    "mat4 viewModel = view * model;\n"
    "gl_Position =  projection * viewModel * totalPosition;\n"
	"TexCoords = tex;\n"
"}\n";


const char *YAVE_FS_ANIM = 
"#version 400 core\n"
"out vec4 FragColor;\n"

"in vec2 TexCoords;\n"

"uniform sampler2D texture_diffuse1;\n"

"void main()\n"
"{\n"    
"    FragColor = texture(texture_diffuse1, TexCoords);\n"
"}\n";


const char *YAVE_VS =
"#version 400 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aNormal;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"out vec2 TexCoord;\n"

"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"uniform float globalWind;\n"
"uniform float windness;\n"

"void main()\n"
"{\n"
"    float tmp = (globalWind)* windness;\n"
"    float tmpY = aPos.y + 0.5f;\n"
"    gl_Position = projection * view  * model* vec4(aPos.x + tmp * tmpY ,aPos.y, aPos.z + tmp * tmpY, 1.0f);\n"
"    TexCoord = aTexCoord;\n"
"}\n";

const char *YAVE_FS =
"#version 400 core \n"

"out vec4 FragColor;\n"

"in vec2 TexCoord;\n"

"uniform sampler2D tex;\n"
"uniform vec4 color;\n"
"uniform bool texturing;\n"
"void main()\n"
"{\n"
"    if(texturing){\n"
"        FragColor = texture(tex, TexCoord) * color;\n"
"    }else{\n"
"        FragColor = color;\n"
"    }\n"
"}\n";