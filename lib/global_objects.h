#ifndef GLOBAL_OBJECTS_H
#define GLOBAL_OBJECTS_H

//global universal structures
struct Block{
    glm::vec3 position;
    uint rotation = 0;
    uint type = 0;
    float windness = 0;
    uint textureID = 0;
    uint textureIDs[6] = {0,0,0,0,0,0};

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