#include "../lib/YAVE_input.h"

YAVE_key YAVE_keys[YAVE_KEY_MAPPED];


void YAVE_exec_keys(void){
        if(YAVE_keys[YAVE_KEY_UP].pressed) cam0.position  += glm::vec3(0.0f, 0.0f, cam0.v_z);
        if(YAVE_keys[YAVE_KEY_DOWN].pressed) cam0.position  += glm::vec3(0.0f, 0.0f, -cam0.v_z);
        if(YAVE_keys[YAVE_KEY_RIGHT].pressed) cam0.position  += glm::vec3(-cam0.v_y, 0.0f, 0.0f);
        if(YAVE_keys[YAVE_KEY_LEFT].pressed) cam0.position  += glm::vec3(cam0.v_z, 0.0f, 0.0f);
        
}


void YAVE_keys_init(void){
    //********************bindings
    YAVE_keys[YAVE_KEY_UP].binding      = GLFW_KEY_W;
    YAVE_keys[YAVE_KEY_DOWN].binding    = GLFW_KEY_S;
    YAVE_keys[YAVE_KEY_RIGHT].binding   = GLFW_KEY_D;
    YAVE_keys[YAVE_KEY_LEFT].binding    = GLFW_KEY_A;

    //****************************
    for(int i=0;i<YAVE_KEY_MAPPED;i++){
        YAVE_keys[i].status=GLFW_RELEASE;
    }
}



//keyboard event
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    for(int i=0;i<YAVE_KEY_MAPPED;i++){
    if (key == YAVE_keys[i].binding){
        YAVE_keys[i].status=action;
        if(action!=GLFW_REPEAT)
            YAVE_keys[i].pressed=action;
    }
    }
}

