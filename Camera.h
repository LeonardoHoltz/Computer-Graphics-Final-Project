#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera
{
private:
    glm::vec3 _position;
    glm::vec3 _viewDirection_n;
    glm::vec3 _upDirection_v;
    glm::vec3 _rightDirection_u;
    float _cameraVelocity;

public:
    // Constructor
    Camera();

    // Getters

    glm::vec3 getPosition();
    glm::vec3 getViewDirection();
    glm::vec3 getUpDirection();
    glm::vec3 getRightDirection();
    float getCameraVelocity();

    // Setters:
    void setPosition(glm::vec3 pos);
    void setViewDirection(glm::vec3 n);
    void setUpDirection(glm::vec3 v);
    void setRightDirection(glm::vec3 u);
    void SetCameraVelocity(float velocity);

    void MoveCamera(glm::vec3 direction);
    void ChangeCameraAbsolutePosition(glm::vec3 newPosition);
    
    void Roll_Z(float angle);
    void Yaw_Y(float angle);
    void Pitch_X(float angle);
};

