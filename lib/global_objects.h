#ifndef GLOBAL_OBJECTS_H
#define GLOBAL_OBJECTS_H


//####################### settings ##################
#define YAVE_x_speed 2.5f //velocity of camera in x axis
#define YAVE_y_speed 2.5f //velocity of camera in y axis
#define YAVE_z_speed 2.5f //velocity of camera in z axis
#define YAVE_rotx_speed 2.5f //velocity of rotation camera in x axis
#define YAVE_roty_speed 2.5f //velocity of rotation camera in y axis
//###################################################


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

extern float deltaTime;	// Time between current frame and last frame
extern float lastFrame; // Time of last frame
extern u_char mode;

extern GLFWwindow* window;

#endif