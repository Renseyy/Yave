#ifndef CAMERA_H
#define CAMERA_H

#include <array>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    DOWNWARD,
    UPWARD
};

enum Camera_Mode {
    CAM_NORMAL, //in-game mode
    CAM_DRONE, //shift:up space:down
    CAM_FREE //free camera mode
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // camera Attributes
    std::array <float,3> Position;
    std::array <float,3> Front;
    std::array <float,3> Up;
    std::array <float,3> Right;
    std::array <float,3> WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    //"fast forward" ;)
    float flash = 1.0f;
    unsigned char mode=CAM_NORMAL;

    // constructor with vectors
    Camera(std::array <float,3> position ={0.0f, 0.0f, 0.0f}, std::array <float,3> up = {0.0f, 1.0f, 0.0f}, float yaw = YAW, float pitch = PITCH);

    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    std::array <std::array <float,4>,4> GetViewMatrix();    //return tablica 4x4

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch);

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset);

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};
#endif