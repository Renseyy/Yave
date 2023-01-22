

#include <glad/glad.h>
#include <cmath>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "lib/Shader.h"
#include "lib/Noise.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

typedef unsigned int uint;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const uint SCR_WIDTH = 800;
const uint SCR_HEIGHT = 600;

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Yet Another Voxel Engine", NULL, NULL); // jeśli chcemy fullscreena to w 4 argumencie można glfwGetPrimaryMonitor(), ale jest to ułomne XD
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
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("shaders/base.vertex.glsl", "shaders/base.fragment.glsl"); // you can name your shader files however you like

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.0f,  1.0f, 0.0f, 
         0.5f,  0.5f,  0.0f,  1.0f, 1.0f, 
         0.5f,  0.5f,  0.0f,  1.0f, 1.0f, 
        -0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 
        -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 

         0.0f, -0.5f,  -0.5f,  0.0f, 0.0f, 
         0.0f, -0.5f,  0.5f,  1.0f, 0.0f, 
         0.0f,  0.5f,   0.5f,  1.0f, 1.0f, 
         0.0f,  0.5f,  0.5f, 1.0f, 1.0f, 
         0.0f, -0.5f,  -0.5f,  0.0f, 0.0f,
         0.0f,  0.5f,  -0.5f,  0.0f, 1.0f, 
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,// top right - back
          0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,// bottom right - back
         -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,// bottom left - back
         -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,// top left - back
          0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,// top right - front
          0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,// bottom right - front
         -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,// bottom left - front
         -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f// top left - front
    };

    uint indices[] = {  // note that we start from 0!
    0, 1, 3,   // back
    1, 2, 3,   
    2, 3, 6,   //left side
    3, 6, 7,
    0, 1, 5,   //right side
    0, 4, 5,
    4, 5, 7,   // front
    5, 6, 7,
    0, 4, 7,   //top
    0, 3, 7,
    1, 2, 6,   //bottom
    1, 5, 6
    }; 


    uint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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
    // render loop
    // -----------
    float oldczas=glfwGetTime()-M_PI/2.0f;
    uint calc = 0;

    //Perlin noise 
    const siv::PerlinNoise::seed_type seed = 123456u;

	const siv::PerlinNoise perlin{ seed };

    //Textures
    unsigned int texture1;
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load("textures/grass.png", &width, &height, &nrChannels, 4);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
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
        
        float val=sin(czas)/2.0f + 0.5f;
        ourShader.use();
      
        
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);
        glm::mat4 model         = glm::mat4(1.0f);
        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        model = glm::rotate(model, 0.25f, glm::vec3(0.0f, 1.0f, 0.0f));

        unsigned int viewLoc  = glGetUniformLocation(ourShader.ID, "view");
        
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("model", model);
        unsigned int addonLoc = glGetUniformLocation(ourShader.ID, "addon");
        glUniform1f(addonLoc,perlin.noise1D_01(val));

        // render the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0,12);
       
        glDrawElements(GL_TRIANGLES, sizeof(indices)/4, GL_UNSIGNED_INT, 0);
        

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
    glViewport(0, 0, width, height);
}

