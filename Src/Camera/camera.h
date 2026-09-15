#pragma once
#include "../Abstraction/abstraction.h"
#include "../../glm-master/glm-master/glm/gtc/matrix_transform.hpp"

class Camera : public Input{
private:
    float Yaw = -90.0f;
    float Pitch = 0.0f;
    glm::vec3 Dir = glm::vec3(0.0f,0.0f,0.0f);

    glm::vec3 CameraPos = glm::vec3(0.0f,0.0f,0.0f);
    const glm::vec3 Up = glm::vec3(0.0f,1.0f,0.0f);
    glm::vec3 CameraFront = glm::vec3(0.0f,0.0f,-1.0f);
    float CameraSpeed = 50.0f;
    const float Sensitivity = 0.1f;
    GLFWwindow* Window = nullptr;

    void camera_cursor_mov();

public:
    explicit Camera(GLFWwindow* window);
    void camera_movement(float delta_time);
    glm::mat4 glm_view();

};