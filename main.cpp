/*
YAVE - by MAKOUS and KK
all rights reserved
*/


//basic libs
#include <iostream>
#include <string>
#include <cmath>

//glad
#include <glad/glad.h>
//glfw
#include <GLFW/glfw3.h>
//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//custom libs
#include "lib/global_objects.h"
#include "lib/Shader.h"
#include "lib/Noise.h"
#include "lib/YAVE_input.h"
//stb - textures
#include "lib/TextureManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "lib/imgui/imgui.h"
#include "lib/imgui/imgui_impl_opengl3_loader.h"
#include "lib/imgui/imgui_impl_opengl3.h"
#include "lib/imgui/imgui_impl_glfw.h"
typedef unsigned int uint;

//functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


// settings
const uint WIDTH = 800;
const uint HEIGHT = 600;
const float ASPECT = float(WIDTH)/HEIGHT;
Camera cam0;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE); //maximize window
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Yet Another Voxel Engine", NULL, NULL); // jeśli chcemy fullscreena to w 4 argumencie można glfwGetPrimaryMonitor(), ale jest to ułomne XD
    if (window == NULL)
    {
        std::cout << "Cus nie pyklo byczq przy tworzenia okna glfw" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //kiedy zmieniamy rozmiar okna wywołaj funkcje która dostosuje opengla do nowego wyświetlania

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD sie wykruszyl, biedaczysko..." << std::endl;
        return -1;
    }
    // Testowanie głębokości
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable( GL_BLEND );
    glEnable(GL_CULL_FACE);  
    glCullFace(GL_BACK);  
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("shaders/base.vertex.glsl", "shaders/base.fragment.glsl"); // you can name your shader files however you like
    
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
    // Back face
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
    // Front face
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
    // Left face
    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
    // Right face
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
    // Bottom face
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
    // Top face
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left        
};
    const uint OBIECT_NUM = 2;
    Block cubePositions[] = {
        {
            position:{0.0f,-1.0f,0.0f},
            rotation: 1,
            type:1,
            textureIDs: {
                5,5,5,5,3,6
            }
        },
        {
            position:{0.0f,0.0f,0.0f},
            windness:1
        }
        
        
    };


    uint VBO, VAO;
    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 


    unsigned char i=0; //nie marnujmy pamięci ;)

    //Perlin noise 
    const siv::PerlinNoise::seed_type seed = 123456u;

	const siv::PerlinNoise perlin{ seed };

    //Textures
    TextureManager textureManager;
    textureManager.loadTextures({
        "textures/azalea_leaves.png",
        "textures/leaves.png",
        "textures/sapling.png",
        "textures/dirt.png",
        "textures/glass.png",
        "textures/grass_block_side.png",
         "textures/grass_block_top.png"

        
        
    });
    
    //init camera
    cam0.position=glm::vec3(0.0f, 0.0f, -4.0f); //starting position
    cam0.v[0]=0.05f; //x sensitivity
    cam0.v[1]=0.05f; //y sensitivity
    cam0.v[2]=0.05f; //z sensitivity
    cam0.rotation_v[0]=glm::radians(0.1f); //rotation x-z sensitivity
    cam0.rotation_v[1]=glm::radians(0.1f); //rotation y sensitivity

    cam0.rotation[0]=0.0f; //starting rotation
    cam0.rotation[1]=0.0f;

    
    
    //keyboard
    YAVE_keys_init();
    glfwSetKeyCallback(window, key_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetCursorPosCallback(window, mouse_callback);

    // render loop
    // -----------
    float oldczas=glfwGetTime()-M_PI/2.0f;
    uint calc = 0;

    
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //takie szare tuo
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        

        //pozmieniajmy kolorki
        float czas = glfwGetTime();
        
        //keyboard
            YAVE_exec_keys();

        //render shaders
        float val=sin(czas)/2.0f + 0.5f;
        ourShader.use();
      
      //set view
      //camera varialibes
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
        //up.x+=cam0.position.x;
        //up.z+=cam0.position.z;
        
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);
        glm::mat4 model         = glm::mat4(1.0f);
        
        view  = glm::rotate(view, cam0.rotation[0], up);
        view  = glm::rotate(view, cam0.rotation[1], glm::cross(cam0.position,up));
        projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

        view  = glm::translate(view, cam0.position);
        unsigned int viewLoc  = glGetUniformLocation(ourShader.ID, "view");
        
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        
        ourShader.setMat4("projection", projection);
        unsigned int addonLoc = glGetUniformLocation(ourShader.ID, "globalWind");
        glUniform1f(addonLoc,perlin.noise1D_01(val));


        // render the triangle
        glBindVertexArray(VAO);
        for(uint i = 0; i < OBIECT_NUM; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i].position);
            model = glm::rotate(model,glm::radians(45.0f),glm::vec3(0,1,0));
            ourShader.setFloat("windness",cubePositions[i].windness);
            ourShader.setMat4("model", model);
            if(cubePositions[i].type == 0){
                glUniform1i(glGetUniformLocation(ourShader.ID, "tex"), cubePositions[i].textureID);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }else{
                for(uint j = 0; j < 6;j++){
                    glUniform1i(glGetUniformLocation(ourShader.ID, "tex"), cubePositions[i].textureIDs[j]);
                    glDrawArrays(GL_TRIANGLES, j*6, 6);
                }
            }
            
            
        }
        

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    int w = height * ASPECT;
    int left = (width - w) / 2;
    glViewport(left, 0, w, height);
}


