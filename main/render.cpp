#include "render.h"

#include <glm/glm.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <Animator.h>
#include <Shader.h>
#include <Model.h>

#include <YAVE_input.h>
#include <yave.h>

extern GLFWwindow* window;
extern float deltaTime,lastFrame;
extern unsigned char YAVE_displayMode;
extern bool show_demo_window;

//global varialibes
glm::mat4 view,projection,model;
unsigned int viewLoc;


void YAVE_executeEvents(void){
    glfwSwapBuffers(window);
    glfwPollEvents(); 

    YAVE_exec_keys();
}



void YAVE_adjustFPS(float frameTime){
    deltaTime = frameTime-lastFrame;
    lastFrame=frameTime;
}

void YAVE_renderImgui(void){
    // gui
    if(YAVE_displayMode==YAVE_MODE_MOUSE || YAVE_displayMode==YAVE_MODE_BACKPACK){
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
    }

    //imgui
        if((YAVE_MODE_MOUSE==YAVE_displayMode) || (YAVE_MODE_BACKPACK==YAVE_displayMode)){
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
}

void YAVE_renderBackground(void){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //takie szare tuo
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void YAVE_prepareRender(void){
    
    YAVE_adjustFPS((float)glfwGetTime());
    YAVE_renderBackground();

}


void YAVE_execAnimation(Animator * animator,Shader * shader){
    animator->UpdateAnimation(deltaTime);
    std::vector<glm::mat4> transforms = animator->GetFinalBoneMatrices();
	for (int i = 0; i < transforms.size(); ++i)
	shader->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
}

void YAVE_renderModel(Shader *shader, Model *renderedModel){
    shader->setBool("Texturing", GL_TRUE);
    shader->setVec4("color", glm::vec4(0.0, 1.0 , 0.0 , 1.0));
	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
        
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -12.0f)); // translate it down so it's at the center of the scene
	//model = glm::scale(model, glm::vec3(.5f, .5f, .5f));	// it's a bit too big for our scene, so scale it down
	shader->setMat4("model", model);
	renderedModel->Draw(*shader);
}

bool YAVE_activeWindow(void){
    return !glfwWindowShouldClose(window);
}