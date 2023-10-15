#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

class Camera;

extern Camera cam;

unsigned char YAVE_initWindow(void);
void YAVE_configureImgui(void);
void YAVE_configureBuffers(void);
void YAVE_configureView(void);
void YAVE_configureInput(void);

void Yave_Init(void);
void Yave_End(void);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

