#include <iostream>
#include <string>
#include <map>
#include <glad/glad.h>
#include <stb_image.h>
#include <stdexcept>
#include <vector>
using namespace std;

/**
 * Jak tego używamy?
 * - dodajemy tekstury jakie chcemy poprzez `addTexture`
 */

struct BufferDescription;
struct TextureStruct{
    BufferDescription* buffer;        // Referencja do bufora
    uint index;
    uint x = 0;          
    int size;          // Wielkość textury, //! musi być większa od TEXTURE_MIN_SIZE
    unsigned char* data;
};
struct BufferDescription{
    int size;
    vector<TextureStruct*> elems;
    bool baked = false;
};
class TextureManager{
    private:
        map<string, TextureStruct> textures;
        BufferDescription* buffers;
        GLint maxTextureUnits = 0;

        BufferDescription* findBufferFor(int size){
            for(uint i = 0; i < maxTextureUnits; ++i){
                if( buffers[i].size == 0 || ( buffers[i].size == size && !buffers[i].baked))
                    return &buffers[i];
            }
            return NULL;
        }
    public:
        TextureManager(){
            //Load max number of texture buffers;
            maxTextureUnits = 32;
            this-> buffers = (BufferDescription*) calloc(maxTextureUnits, sizeof(BufferDescription));
        }
        TextureStruct& addTexture(string src){
            //Mamy już taką teksturę w pamięci
            cout<<endl<<"[0] Dodawanie: "<<src<<endl;
            if (textures.count(src)){
                cout<<endl<<"[1] Znaleziono, zwracam referencję do: "<<src<<endl;
                return textures[src];
            }
                
            //Tworzymy stukturę
            cout<<endl<<"[1] Nie znaleziono: "<<src<<endl;
            textures[src] = TextureStruct();
            TextureStruct* tex = &textures[src];
            //Załaduj dane tekstury
            stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis
            int  height, nrChannels;
            tex->data = stbi_load(src.c_str(), &tex->size, &height, &nrChannels, 4);
            if (!tex->data){
                throw new runtime_error("Nie udało się wczytać tekstury[ "+ src + "]");
                exit(-1);
            }
            if (tex->size != height){
                throw new runtime_error("Tekstura nie jest kwadratowa tylko prostokątna - nie wspieramy");
                exit(-1);
            }
            cout<<endl<<"[2] Załadowano teksturę: "<<src<<endl;
            cout<<"[*] Wymiary: "<<tex->size<<endl;
            // Znajdź bufor do którego możemy się wczytać 
            BufferDescription* buffer = this->findBufferFor(tex->size);
            if(buffer == NULL){
                throw new runtime_error("Nie można znalesć już żadnego wolnego bufora");
                exit(-1);
            }
            cout<<endl<<"[3] Znaleziono wolny bufor: (BufferDescription "<<buffer<<")"<<endl;
            cout<<"[*] Wielkość: "<<buffer->size<<endl;
            cout<<"[*] Ilość elementów: "<<buffer->elems.size()<<" ("<<buffer->elems.size()+1<<")"<<endl;
            buffer->size = tex->size;
            buffer->elems.push_back(tex);
            tex->buffer = buffer;

            cout<<endl<<"[4] Dodano!"<<endl;
            
        }
        void bakeBuffer(uint index){
            if(!(index < maxTextureUnits)){
                throw new runtime_error("Podany index jest za duży");
                exit(-1);
            }
            BufferDescription * buffer = &buffers[index];
            if(buffer->baked){
                throw new runtime_error("Ten bufor został już wypieczony");
                exit(-1);
            }
            if(buffer->size == 0 || buffer->elems.size() == 0){
                throw new runtime_error("Ten bufor nie zawiera danych, nie można go wypiec");
                exit(-1);
            }
            uint count = buffer->elems.size();
        }
        void loadTextures(vector<string> textures){
            // uint num = textures.size();
            // this->textures = (uint *) malloc(num * sizeof(uint));
            // glGenTextures(num,this->textures);
            // for(uint i =0; i < textures.size();i++){
            //     int width, height, nrChannels;
            //     stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
            //     unsigned char *data = stbi_load(textures[i].c_str(), &width, &height, &nrChannels, 4);
            //     if (data)
            //     {
                    
            //         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            //         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            //         // set texture filtering parameters
            //         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            //         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            //         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

            //         glActiveTexture(GL_TEXTURE1 + i);
            //         glBindTexture(GL_TEXTURE_2D, this->textures[i]);
            //         cout<<"Loaded texture[ "+textures[i]+"] { " + to_string(i) +" }"<<endl;
            //     }
            //     else
            //     {
            //         std::cout << "Failed to load texture" << std::endl;
            //     }
            //     stbi_image_free(data);
            // }
            
        }
};