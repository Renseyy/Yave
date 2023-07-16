/*
YAVE - by MAKOUS and KK
all rights reserved
*/

#include "global.h"

//stb - textures
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <unistd.h>
//main files
#include "main/config.h"
#include "main/render.h"

irrklang::vec3df vec3glm_toklang(glm::vec3 x){
    return irrklang::vec3df(x.x,x.r,x.s);
}

#include <fstream>
// aby możliwie najbardziej zwiększyć czytelnosc kodu nalezy unikac pisania duzych fragmentow kodu w main()
// zamiast tego mozna umieszczac wlasne funkcje w config i render i je wywolywac w main

#include "lib/lone/main.hpp"
int main()
{
    Lone::initLone();
    std::cout.sync_with_stdio(false);
    // manager.addTexture("textures/dirt.png");
    // manager.addTexture("textures/glass.png");
    // manager.addTexture("textures/oak.png");
    // manager.addTexture("textures/grenny.png");
    // manager.addTexture("textures/dirt.png");
    // YAVE_initWindow();
    // YAVE_configureImgui();
    // YAVE_configureBuffers();
    // YAVE_configureView();
    // YAVE_configureInput();

	// stbi_set_flip_vertically_on_load(true);
    
    // //sound
    // irrklang::ISoundEngine * sound = irrklang::createIrrKlangDevice();

    // if(!sound){
    //     cout<<"Sound Error <sad sound>"<<endl;
    //     return 0;
    // }
	// // build and compile shaders
	// // -------------------------
	// Shader ourShader("shaders/animations/anim_model.vs", "shaders/animations/anim_model.fs"); //dla animacji
    // //Shader ourShader("shaders/base.vertex.glsl", "shaders/base.fragment.glsl"); //nie dla animacji
	
	// // load models
	// // -----------
    // cout<<"loading model..."<<endl;
    // //Model ourModel("models/cube.glb");
	// Model ourModel("animations/Ymca_Dance/Ymca_Dance.dae");

	// Animation danceAnimation("animations/Ymca_Dance/Ymca_Dance.dae",&ourModel);
    // Animator animator(&danceAnimation);
    
    // cout<<"loaded"<<endl;
    
    // //sound->play2D("sound/YMCA.ogg", true); //NOTE: true - zapętla, false - bez zapętlenia
    // glm::vec3 musicPosition = glm::vec3(0,0,0);
    // irrklang::ISound* music = sound->play3D("sound/getout.ogg",irrklang::vec3df(0,0,0), true, false, true);
    // if (music)
    //   music->setMinDistance(5.0f);

    // sound->setListenerPosition(irrklang::vec3df(0,0,0),irrklang::vec3df(0,0,1));
    // //render loop
    // while (!glfwWindowShouldClose(window))
    // {
    //     YAVE_prepareRender(&ourShader);

    //     YAVE_execAnimation(&animator,&ourShader);
        
    //     YAVE_renderModel(&ourShader,&ourModel);
    //     sound->setListenerPosition(vec3glm_toklang(cam0.Position),vec3glm_toklang(cam0.Front));
    // }
    // if (music)
    //   music->drop(); // release music stream.
    // sound->drop(); // delete sound engine
    // glfwTerminate();
	return 0;
}



