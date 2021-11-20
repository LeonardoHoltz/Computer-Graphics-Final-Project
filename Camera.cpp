#include "Camera.h"

Camera g_Cam;

Camera::Camera() {
    setPosition(glm::vec3(0.5f, 0.0f, 10.0f));
    setViewDirection(glm::vec3(0.0f, 0.0f, -1.0f));
    setUpDirection(glm::vec3(0.0f, 1.0f, 0.0f));
    setRightDirection(glm::vec3(1.0f, 0.0f, 0.0f));
    SetCameraVelocity(1.0f);
}

glm::vec3 Camera::getPosition() {
    return _position;
}

glm::vec3 Camera::getViewDirection() {
    return _viewDirection_n;
}

glm::vec3 Camera::getUpDirection() {
    return _upDirection_v;
}

glm::vec3 Camera::getRightDirection() {
    return _rightDirection_u;
}

float Camera::getCameraVelocity() {
    return _cameraVelocity;
}

void Camera::setPosition(glm::vec3 pos) {
    _position = pos;
}

void Camera::setViewDirection(glm::vec3 n) {
    _viewDirection_n = n;
}

void Camera::setUpDirection(glm::vec3 v) {
    _upDirection_v = v;
}

void Camera::setRightDirection(glm::vec3 u) {
    _rightDirection_u = u;
}

void Camera::SetCameraVelocity(float velocity) {
    _cameraVelocity = velocity;
}

void Camera::MoveCamera(glm::vec3 direction) {
    setPosition(getPosition() + (direction * getCameraVelocity()));
}

/* ROTATIONS */

void Camera::Roll_Z(float angle) {
    setRightDirection((getRightDirection() * cos(angle)) + (getUpDirection() * sin(angle)));
    setUpDirection((-1.0f * getRightDirection() * sin(angle)) + (getUpDirection() * cos(angle)));
}
void Camera::Yaw_Y(float angle) {
    setRightDirection((getRightDirection() * cos(angle)) + (getViewDirection() * sin(angle)));
    setViewDirection((-1.0f * getRightDirection() * sin(angle)) + (getViewDirection() * cos(angle)));
}
void Camera::Pitch_X(float angle) {
    setUpDirection((getUpDirection() * cos(angle)) + (getViewDirection() * sin(angle)));
    setViewDirection((-1.0f * getUpDirection() * sin(angle)) + (getViewDirection() * cos(angle)));
}

/* MATRIX OPERATIONS */

glm::mat4 Camera::View() {
    return glm::lookAt(getPosition(), getPosition() + getViewDirection(), getUpDirection());
}

glm::mat4 Camera::Projection(float hfov, float vfov, float nearPlane, float farPlane) {
    hfov = glm::radians(hfov);
    vfov = glm::radians(vfov);
    float aspectRatio = glm::tan(hfov / 2.0f) / glm::tan(vfov / 2.0f);
    return glm::perspective(vfov, aspectRatio, nearPlane, farPlane);
}

void Camera::UpdateCamera() {

    // Camera Translation
    if (g_Input.key_states[GLFW_KEY_W].is_down)
    {
        MoveCamera(glm::vec3(0.0f, 0.0f, -1.0f)); // remember: the forward of the camera is Z negative!
    }
    if (g_Input.key_states[GLFW_KEY_A].is_down)
    {
        MoveCamera(glm::vec3(-1.0f, 0.0f, 0.0f));
    }
    if (g_Input.key_states[GLFW_KEY_S].is_down)
    {
        MoveCamera(glm::vec3(0.0f, 0.0f, 1.0f));
    }
    if (g_Input.key_states[GLFW_KEY_D].is_down)
    {
        MoveCamera(glm::vec3(1.0f, 0.0f, 0.0f));
    }
    if (g_Input.key_states[GLFW_KEY_SPACE].is_down)
    {
        MoveCamera(glm::vec3(0.0f, 1.0f, 0.0f));
    }
    if (g_Input.key_states[GLFW_KEY_LEFT_CONTROL].is_down)
    {
        MoveCamera(glm::vec3(0.0f, -1.0f, 0.0f));
    }
}