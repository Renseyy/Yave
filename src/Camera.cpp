#include <Camera.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> //for casting
#include <glm/gtc/matrix_transform.hpp>

glm::vec3 float3_to_vec3(std::array <float,3> vector){
    return glm::vec3(vector[0],vector[1],vector[2]);
}

std::array <float,3> vec3_to_float3(glm::vec3 vector){
    std::array <float,3> tmptab={vector[0],vector[1],vector[2]};
    return tmptab;
}

std::array <std::array <float,4>,4> mat4_to_float4x4(glm::mat4 matrix){
    std::array <std::array <float,4>,4> tmptab;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            tmptab[i][j]=matrix[i][j];
        }
    }
    return tmptab;
}

Camera::Camera(std::array <float,3> position, std::array <float,3> up, float yaw, float pitch) : Front({0.0f, 0.0f, -1.0f}), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM){
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front({0.0f, 0.0f, -1.0f}), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM){
    Position = {posX, posY, posZ};
    WorldUp = {upX, upY, upZ};
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

std::array <std::array <float,4>,4> Camera::GetViewMatrix(){
    return mat4_to_float4x4(glm::lookAt(float3_to_vec3(Position), float3_to_vec3(Position) + float3_to_vec3(Front), float3_to_vec3(Up)));
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime){
    glm::vec3 tmpFront, tmpRight, tmpUp;

    if(mode==CAM_NORMAL || mode==CAM_DRONE){
        tmpFront=glm::vec3(cos(glm::radians(Yaw)),0,sin(glm::radians(Yaw)));
        tmpRight=glm::normalize(glm::cross(tmpFront, float3_to_vec3(WorldUp)));;
        tmpUp=float3_to_vec3(WorldUp);
    }
    else if(mode==CAM_FREE){
        tmpFront=float3_to_vec3(Front);
        tmpRight=float3_to_vec3(Right);
        tmpUp=float3_to_vec3(Up);
    }
    float velocity = MovementSpeed * deltaTime;
    glm::vec3 tmpPosition=float3_to_vec3(Position);

    if (direction == FORWARD)
        tmpPosition += tmpFront * velocity * flash;
    if (direction == BACKWARD)
        tmpPosition -= tmpFront * velocity * flash;
    if (direction == LEFT)
        tmpPosition -= tmpRight * velocity * flash;
    if (direction == RIGHT)
        tmpPosition += tmpRight * velocity * flash;
    if (direction == DOWNWARD)
        tmpPosition -= tmpUp * velocity * flash;
    if (direction == UPWARD)
        tmpPosition += tmpUp * velocity * flash;

    Position = {tmpPosition[0],tmpPosition[1],tmpPosition[2]};
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true){
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw   += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset){
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}


void Camera::updateCameraVectors(){
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front = glm::normalize(front);
    Front = {front[0],front[1],front[2]};
    // also re-calculate the Right and Up vector

    glm::vec3 tmpVector = glm::normalize(glm::cross(front, float3_to_vec3(WorldUp)));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Right = {tmpVector[0],tmpVector[1],tmpVector[2]};
    tmpVector = glm::normalize(glm::cross(float3_to_vec3(Right), front));
    Up    = {tmpVector[0],tmpVector[1],tmpVector[2]};
}