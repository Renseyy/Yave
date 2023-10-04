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

#include <Object.h>
#include <Listener.h>
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
    
    Object obj1,obj2;
    obj1.isAnimated=true;
    obj1.ModelFile=DIRECT_DIR("animations/Ymca_Dance/Ymca_Dance.dae");

    obj1.AnimationFile=DIRECT_DIR("animations/Ymca_Dance/Ymca_Dance.dae");
    obj1.SoundFile=DIRECT_DIR("music/YMCA.wav");
    obj1.position={0.0f,0.0f,-12.0f};
    obj1.Init();

    obj2.noSound=true;
    obj2.ModelFile=DIRECT_DIR("models/cube.glb");
    obj2.position={1.0f,1.0f, -4.0f};
    obj2.Init();

    obj1.sound->Play();

    while (!glfwWindowShouldClose(window))
    {
        YAVE_executeEvents();
        YAVE_prepareRender();

        UpdateListener();

        obj1.Render();
        obj2.Render();
    }

    

    Sound_DeleteListener();
    glfwTerminate();
	return 0;
}



