#include "render.h"

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

void YAVE_prepareRender(Shader * shader){
    YAVE_executeEvents();
    YAVE_adjustFPS((float)glfwGetTime());
    YAVE_renderBackground();

    shader->use();

	view          = glm::mat4(1.0f);
    projection    = glm::mat4(1.0f);
    model         = glm::mat4(1.0f);

    projection = glm::perspective(glm::radians(45.0f), YAVE_ratio , 0.1f, 3000.0f);


    view  = cam0.GetViewMatrix();
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

    shader->setMat4("projection", projection);
    shader->setMat4("view", view);
}


void YAVE_execAnimation(Animator * animator,Shader * shader){
    animator->UpdateAnimation(deltaTime);
    std::vector<glm::mat4> transforms = animator->GetFinalBoneMatrices();
	for (int i = 0; i < transforms.size(); ++i)
	shader->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
}

void YAVE_renderModel(Shader *shader, Model *renderedModel){
    shader->setBool("Texturing", GL_FALSE);
    shader->setVec4("color", glm::vec4(0.0, 1.0 , 0.0 , 1.0));
	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
        
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	//model = glm::scale(model, glm::vec3(.5f, .5f, .5f));	// it's a bit too big for our scene, so scale it down
	shader->setMat4("model", model);
	renderedModel->Draw(*shader);
}