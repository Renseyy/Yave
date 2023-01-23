#include <vector>
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <stb_image.h>
using namespace std;
class TextureManager{
    public:
        void loadTextures(vector<string> textures){
            uint num = textures.size();
            this->textures = (uint *) malloc(num * sizeof(uint));
            glGenTextures(num,this->textures);
            for(uint i =0; i < textures.size();i++){
                int width, height, nrChannels;
                stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
                unsigned char *data = stbi_load(textures[i].c_str(), &width, &height, &nrChannels, 4);
                if (data)
                {
                    
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                    // set texture filtering parameters
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

                    glActiveTexture(GL_TEXTURE1 + i);
                    glBindTexture(GL_TEXTURE_2D, this->textures[i]);
                    cout<<"Loaded texture[ "+textures[i]+"] { " + to_string(i) +" }"<<endl;
                }
                else
                {
                    std::cout << "Failed to load texture" << std::endl;
                }
                stbi_image_free(data);
            }
            
        }
    private:
        uint * textures;
};