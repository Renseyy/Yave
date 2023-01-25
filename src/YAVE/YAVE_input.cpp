#include "../../lib/YAVE_input.h"

YAVE_key YAVE_keys[YAVE_KEY_MAPPED];

//global varialibes
float lastX , lastY;
double xoffset, yoffset;
float flash;
bool firstMouse;
bool mode_block;

void YAVE_keys_init(void){
    xoffset=0;
    yoffset=0;
    mode_block=false;
    flash=3.0f;
    firstMouse=true;
    //********************bindings
    YAVE_keys[YAVE_KEY_UP].binding      = GLFW_KEY_W;
    YAVE_keys[YAVE_KEY_DOWN].binding    = GLFW_KEY_S;
    YAVE_keys[YAVE_KEY_RIGHT].binding   = GLFW_KEY_D;
    YAVE_keys[YAVE_KEY_LEFT].binding    = GLFW_KEY_A;
    YAVE_keys[YAVE_KEY_SHIFT].binding   = GLFW_KEY_LEFT_SHIFT;
    YAVE_keys[YAVE_KEY_SPACE].binding   = GLFW_KEY_SPACE;
    YAVE_keys[YAVE_KEY_CTRL].binding    = GLFW_KEY_LEFT_CONTROL;
    YAVE_keys[YAVE_KEY_TAB].binding     = GLFW_KEY_TAB;
    //YAVE_keys[YAVE_ARROW_UP].binding    = GLFW_KEY_UP;
    //YAVE_keys[YAVE_ARROW_DOWN].binding    = GLFW_KEY_DOWN;
    //YAVE_keys[YAVE_ARROW_RIGHT].binding    = GLFW_KEY_RIGHT;
    //YAVE_keys[YAVE_ARROW_LEFT].binding    = GLFW_KEY_LEFT;
    //****************************
    for(int i=0;i<YAVE_KEY_MAPPED;i++){
        YAVE_keys[i].status=GLFW_RELEASE;
    }
}


void YAVE_exec_keys(void){
    if(mode==YAVE_MODE_NORMAL || mode==YAVE_MODE_BACKPACK){ 
        if(YAVE_keys[YAVE_KEY_UP].pressed) cam0.ProcessKeyboard(FORWARD,deltaTime);     
         if(YAVE_keys[YAVE_KEY_DOWN].pressed) cam0.ProcessKeyboard(BACKWARD,deltaTime);
        if(YAVE_keys[YAVE_KEY_RIGHT].pressed) cam0.ProcessKeyboard(RIGHT,deltaTime);
        if(YAVE_keys[YAVE_KEY_LEFT].pressed) cam0.ProcessKeyboard(LEFT,deltaTime);
    }
       // if(YAVE_keys[YAVE_KEY_SHIFT].pressed) cam0.position  += glm::vec3(0, cam0.v[1] , 0);
       // if(YAVE_keys[YAVE_KEY_SPACE].pressed) cam0.position  -= glm::vec3(0, cam0.v[1] , 0);

        if(YAVE_keys[YAVE_KEY_TAB].pressed){
            if(!mode_block){
                if(mode==YAVE_MODE_NORMAL){
                    firstMouse = true;
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);    
                    mode=YAVE_MODE_MOUSE;
                }
                else if(mode == YAVE_MODE_MOUSE){
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                    mode=YAVE_MODE_BACKPACK;
                }
                else if(mode == YAVE_MODE_BACKPACK){
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                    mode=YAVE_MODE_NORMAL;
                }   //może być w przyszłości więcej trybów
                mode_block=true;
            }
        }else{
            if(mode_block){
                mode_block=false;
            }
        }
        //if(YAVE_keys[YAVE_ARROW_UP].pressed) cam0.rotation[1]  -= cam0.rotation_v[1];
        //if(YAVE_keys[YAVE_ARROW_DOWN].pressed) cam0.rotation[1]  += cam0.rotation_v[1];
        //if(YAVE_keys[YAVE_ARROW_RIGHT].pressed) cam0.rotation[0]  += cam0.rotation_v[0];
        //if(YAVE_keys[YAVE_ARROW_LEFT].pressed) cam0.rotation[0]  -= cam0.rotation_v[0];

        //if(cam0.rotation[0]>M_PI) cam0.rotation[0]-=2*M_PI;
        //if(cam0.rotation[0]<-M_PI) cam0.rotation[0]+=2*M_PI;
}




//keyboard event
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //when to exit
        glfwSetWindowShouldClose(window, true);


    //cam0.v[0]=YAVE_x_speed * deltaTime; //x sensitivity
    //cam0.v[1]=YAVE_y_speed * deltaTime; //y sensitivity
    //cam0.v[2]=YAVE_z_speed * deltaTime; //z sensitivity
    //cam0.rotation_v[0]=glm::radians(YAVE_rotx_speed) * deltaTime; //rotation x-z sensitivity
    //cam0.rotation_v[1]=glm::radians(YAVE_roty_speed) * deltaTime; //rotation y sensitivity

    for(int i=0;i<YAVE_KEY_MAPPED;i++){
    if (key == YAVE_keys[i].binding){
        YAVE_keys[i].status=action;
        if(action!=GLFW_REPEAT)
            YAVE_keys[i].pressed=action;
    }
    }
}
//XD
void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if(mode==YAVE_MODE_NORMAL){
    if (firstMouse) //ustaw poczatkowe parametry
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    xoffset=-lastX+xpos;
    yoffset=lastY-ypos;
        lastX = xpos;
        lastY = ypos;
    cam0.ProcessMouseMovement(xoffset*deltaTime,yoffset*deltaTime,true);
    }
} 