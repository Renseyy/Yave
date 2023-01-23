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
    glm::vec3 rotation;
    float v_x; //x velocity
    float v_y; //y velocity
    float v_z; //z velocity
};

extern Camera cam0;

#endif