#pragma once

#include "../global.h"

extern Camera cam0;

u_char YAVE_initWindow(void);
void YAVE_configureImgui(void);
void YAVE_configureBuffers(void);
void YAVE_configureView(void);
void YAVE_configureInput(void);


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

