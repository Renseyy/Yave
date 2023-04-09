#pragma once

/*

This is the file to hold all global includes and varialibes that should be accesibly in every file

*/

//***************************************** includes *********************************************
//basic libs
#include <iostream>
#include <string>
#include <cmath>
//glad
#include <glad/glad.h>
//glfw
#include <GLFW/glfw3.h>
#include "lib/imgui/imgui.h"
#include "lib/imgui/imgui_impl_opengl3.h"
#include "lib/imgui/imgui_impl_glfw.h"
//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//audio
#include <irrklang/irrKlang.h>

//custom libs
#include "lib/global_objects.h"
#include "lib/Shader.h"
#include "lib/Camera.h"
#include "lib/Animator.h"
#include "lib/Model.h"
#include "lib/SimplexNoise.h"
#include "lib/YAVE_input.h"

//texture manager - to update
#include "lib/TextureManager.h"





//***************************************** settings *******************************************
const uint WIDTH = 800;
const uint HEIGHT = 600;

//***************************************** functions ******************************************

//***************************************** global varialibes **********************************
//* declared in main/config.cpp
extern GLFWwindow* window;

extern bool show_demo_window;

extern float deltaTime;
extern float lastFrame;
extern u_char YAVE_displayMode; 


extern Camera cam0;
extern float YAVE_ratio;


//* declared in main/render.cpp
extern glm::mat4 view,projection,model;
extern unsigned int viewLoc;
