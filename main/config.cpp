#include "config.h"

//zmienne globalne
bool show_demo_window;
uint VBO, VAO;

GLFWwindow* window;

float deltaTime;
float lastFrame;
u_char YAVE_displayMode;
 
Camera cam0;
float YAVE_ratio;



/*
initializes window for engine
returns 0 if everything is okey
*/
u_char YAVE_initWindow(void){
    YAVE_ratio=(float)WIDTH / (float)HEIGHT;
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
    window = glfwCreateWindow(WIDTH, HEIGHT, "Yet Another Voxel Engine", NULL, NULL); // jeśli chcemy fullscreena to w 4 argumencie można glfwGetPrimaryMonitor(), ale jest to ułomne XD
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
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable( GL_BLEND );
    //glEnable(GL_CULL_FACE);  
    glCullFace(GL_NONE);  
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glEnable(GL_DEPTH_TEST);

    return 0;
}

void YAVE_configureImgui(void){
    bool show_demo_window = true;

    //IM_GUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");   
}


void YAVE_configureBuffers(void){
    //na razie dodatkowe bufory były niepotrzebne
}



void YAVE_configureView(void){

    YAVE_displayMode=YAVE_MODE_NORMAL;

    //adjust FPS
    deltaTime=0.0f;
    lastFrame=0.0f;

    cam0.Position=glm::vec3(0.0f,0.0f,4.0f);
    cam0.MouseSensitivity=2.5f;
    cam0.mode=CAM_DRONE;
}


void YAVE_configureInput(void){
    //keyboard
    YAVE_keys_init();
    glfwSetKeyCallback(window, key_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetCursorPosCallback(window, mouse_callback);
}






// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    YAVE_ratio=(float)width/(float)height;
}
