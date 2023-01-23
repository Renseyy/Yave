#include "../lib/YAVE_input.h"

YAVE_key YAVE_keys[YAVE_KEY_MAPPED];

float lastX , lastY;

void YAVE_exec_keys(void){
    float dy=glm::sin(cam0.rotation[1]);
    float ndy=glm::cos(cam0.rotation[1]);
    float dx=glm::sin(cam0.rotation[0]) * ndy;
    float dz=glm::cos(cam0.rotation[0]) * ndy;
     
        if(YAVE_keys[YAVE_KEY_UP].pressed) cam0.position  += glm::vec3(-cam0.v[0]*dx, 0/*cam0.v[1]*dy*/, cam0.v[2]*dz);
        if(YAVE_keys[YAVE_KEY_DOWN].pressed) cam0.position  += glm::vec3(cam0.v[0]*dx, 0/*-cam0.v[1]*dy*/, -cam0.v[2]*dz);
        if(YAVE_keys[YAVE_KEY_RIGHT].pressed) cam0.position  += glm::vec3(-cam0.v[0]*dz , 0, -cam0.v[2]*dx);
        if(YAVE_keys[YAVE_KEY_LEFT].pressed) cam0.position  += glm::vec3(cam0.v[0]*dz, 0 , cam0.v[2]*dx);
        //if(YAVE_keys[YAVE_ARROW_UP].pressed) cam0.rotation[1]  -= cam0.rotation_v[1];
        //if(YAVE_keys[YAVE_ARROW_DOWN].pressed) cam0.rotation[1]  += cam0.rotation_v[1];
        //if(YAVE_keys[YAVE_ARROW_RIGHT].pressed) cam0.rotation[0]  += cam0.rotation_v[0];
        //if(YAVE_keys[YAVE_ARROW_LEFT].pressed) cam0.rotation[0]  -= cam0.rotation_v[0];

        if(cam0.rotation[0]>M_PI) cam0.rotation[0]-=2*M_PI;
        if(cam0.rotation[0]<-M_PI) cam0.rotation[0]+=2*M_PI;
}


void YAVE_keys_init(void){
    lastX = 400;
    lastY = 300;
    //********************bindings
    YAVE_keys[YAVE_KEY_UP].binding      = GLFW_KEY_W;
    YAVE_keys[YAVE_KEY_DOWN].binding    = GLFW_KEY_S;
    YAVE_keys[YAVE_KEY_RIGHT].binding   = GLFW_KEY_D;
    YAVE_keys[YAVE_KEY_LEFT].binding    = GLFW_KEY_A;
    //YAVE_keys[YAVE_ARROW_UP].binding    = GLFW_KEY_UP;
    //YAVE_keys[YAVE_ARROW_DOWN].binding    = GLFW_KEY_DOWN;
    //YAVE_keys[YAVE_ARROW_RIGHT].binding    = GLFW_KEY_RIGHT;
    //YAVE_keys[YAVE_ARROW_LEFT].binding    = GLFW_KEY_LEFT;
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

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    float dx = xpos - lastX;
    float dy = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;
    cam0.rotation[0] += cam0.rotation_v[0] * dx;
    cam0.rotation[1] += -cam0.rotation_v[1] * dy;

    //no more than 90 degrees up and down
    if(cam0.rotation[1]>M_PI/2.0f) cam0.rotation[1]= M_PI/2.0f;
    if(cam0.rotation[1]<-M_PI/2.0f) cam0.rotation[1]= -M_PI/2.0f;
}