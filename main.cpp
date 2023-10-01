/*
YAVE - by MAKOUS and KK
all rights reserved
*/

//all global includes and varialibes
#include "global.h"
//stb - textures
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <unistd.h>
//main files
#include <version_config.h>
#include "main/config.h"
#include "main/render.h"

//YAAL
#include <Sound.h>
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
    
    Sound_CreateListener();
    
    
	// build and compile shaders
	// -------------------------
	Shader ourShader(DIRECT_DIR("shaders/animations/anim_model.vs"), DIRECT_DIR("shaders/animations/anim_model.fs")); //dla animacji
    //Shader ourShader(DIRECT_DIR("shaders/base.vertex.glsl"),DIRECT_DIR("shaders/base.fragment.glsl")); //nie dla animacji
    // load models
	// -----------
    cout<<"loading model..."<<endl;
    //Model ourModel(DIRECT_DIR("models/cube.glb"));
	Model ourModel(DIRECT_DIR("animations/Ymca_Dance/Ymca_Dance.dae"));

	Animation danceAnimation(DIRECT_DIR("animations/Ymca_Dance/Ymca_Dance.dae"),&ourModel);
    Animator animator(&danceAnimation);
    
    std::cout<<"loaded"<<std::endl;
    Sound npc;
    npc.Open(DIRECT_DIR("music/YMCA.wav"));
    npc.CreateSource();
    npc.Play();

    while (!glfwWindowShouldClose(window))
    {
        npc.Update();
        
        float x=cam0.Position[0];
        float y=cam0.Position[1];
        float z=cam0.Position[2];

        float * orientation;
        orientation=new float[6];

        for(int v=0;v<3;v++){
            orientation[v]=cam0.Up[v];
            orientation[v+3]=-cam0.Front[v];
        }
        
        float o_y=cam0.Position[1];
        float o_z=cam0.Position[2];
        Sound_SetListenerPosition(x,y,z);
        Sound_SetListenerOrientation(orientation);
        YAVE_executeEvents();
        YAVE_prepareRender(&ourShader);

        YAVE_execAnimation(&animator,&ourShader);
        
        YAVE_renderModel(&ourShader,&ourModel);
      
    }
    Sound_DeleteListener();
    glfwTerminate();
	return 0;
}



