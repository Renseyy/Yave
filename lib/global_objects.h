#ifndef GLOBAL_OBJECTS_H
#define GLOBAL_OBJECTS_H

//global universal structures
struct Block{
    glm::vec3 position;
    uint rotation = 0;
    uint type = 0;
    float windness = 0;
    uint textureID = 0;
    uint textureIDs[6] = {
        0,  //Tył
        0,  // Przód
        0,  // Lewo
        0,  // Prawo
        0,  // Dół
        0   //Góra
    };


};

struct Camera{
    glm::vec3 position;
    float rotation[2]; //rotation
    float v[3]; //velocity
    float rotation_v[2]; //rotation velocity
};

extern Camera cam0;
extern float lastX , lastY;
#endif