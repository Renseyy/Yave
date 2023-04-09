/*
YAVE - by MAKOUS and KK
all rights reserved
*/

//all global includes and varialibes
#include "global.h"

//stb - textures
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

//main files
#include "main/config.h"
#include "main/render.h"
// aby możliwie najbardziej zwiększyć czytelnosc kodu nalezy unikac pisania duzych fragmentow kodu w main()
// zamiast tego mozna umieszczac wlasne funkcje w config i render i je wywolywac w main




int main()
{
    YAVE_initWindow();
    YAVE_configureImgui();
    YAVE_configureBuffers();
    YAVE_configureView();
    YAVE_configureInput();

	stbi_set_flip_vertically_on_load(true);
    
    //sound
    irrklang::ISoundEngine * sound = irrklang::createIrrKlangDevice();

    if(!sound){
        cout<<"Sound Error <sad sound>"<<endl;
        return 0;
    }
	// build and compile shaders
	// -------------------------
	Shader ourShader("shaders/animations/anim_model.vs", "shaders/animations/anim_model.fs"); //dla animacji
    //Shader ourShader("shaders/base.vertex.glsl", "shaders/base.fragment.glsl"); //nie dla animacji
	
	// load models
	// -----------
    cout<<"loading model..."<<endl;
    //Model ourModel("models/cube.glb");
	Model ourModel("animations/Ymca_Dance/Ymca_Dance.dae");

	Animation danceAnimation("animations/Ymca_Dance/Ymca_Dance.dae",&ourModel);
    Animator animator(&danceAnimation);
    
    cout<<"loaded"<<endl;
    
    sound->play2D("sound/YMCA.ogg", true); //NOTE: true - zapętla, false - bez zapętlenia

    //render loop
    while (!glfwWindowShouldClose(window))
    {
        YAVE_prepareRender(&ourShader);

        YAVE_execAnimation(&animator,&ourShader);
        
        YAVE_renderModel(&ourShader,&ourModel);
        
    }
    sound->drop(); // delete sound engine
    glfwTerminate();
	return 0;
}



