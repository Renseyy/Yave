#ifndef GLOBAL_OBJECTS_H
#define GLOBAL_OBJECTS_H

//global universal structures
struct Block{
    glm::vec3 position;
    int texture;
    float windness;
};

struct Camera{
    glm::vec3 position;
    float rotation[2]; //rotation
    float v[3]; //velocity
    float rotation_v[2]; //rotation velocity
};

extern Camera cam0;

#endif