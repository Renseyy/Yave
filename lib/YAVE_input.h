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

#include "global_objects.h"

#define YAVE_KEY_MAPPED 4 //number of mapped keys

struct YAVE_key{
char binding;
u_char status;
u_char pressed;
};

extern YAVE_key YAVE_keys[YAVE_KEY_MAPPED];


void YAVE_exec_keys(void);
void YAVE_keys_init(void);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);



enum { //kiedy edytujesz to, to pamietaj aby zmienić YAVE_KEY_MAPPED i w YAVE_keys_init dodać binding
    YAVE_KEY_UP = 0,
    YAVE_KEY_DOWN,
    YAVE_KEY_RIGHT,
    YAVE_KEY_LEFT
};



#endif