#ifndef YAVE_INPUT_H
#define YAVE_INPUT_H

//glad
#include <glad/glad.h>
//glfw
#include <GLFW/glfw3.h>
//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "global_objects.h"

#include <vector>
#include <iostream>

#define YAVE_FLASH 3.0f //how many faster should it go
#define YAVE_KEY_MAPPED 8 //number of mapped keys

extern bool firstMouse;
extern bool mode_block;
extern Camera cam0;
struct YAVE_key{
uint binding;
u_char status;
u_char pressed;
};

extern YAVE_key YAVE_keys[YAVE_KEY_MAPPED];

//functions
void YAVE_exec_keys(void);
void YAVE_keys_init(void);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);


enum { //kiedy edytujesz to, to pamietaj aby zmienić YAVE_KEY_MAPPED i w YAVE_keys_init dodać binding
    YAVE_KEY_UP = 0,
    YAVE_KEY_DOWN,
    YAVE_KEY_RIGHT,
    YAVE_KEY_LEFT,
    YAVE_KEY_SHIFT,
    YAVE_KEY_SPACE,
    YAVE_KEY_CTRL,
    YAVE_KEY_TAB
    //YAVE_ARROW_UP,
    //YAVE_ARROW_DOWN,
    //YAVE_ARROW_RIGHT,
    //YAVE_ARROW_LEFT
};



#endif