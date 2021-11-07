#include "Camera.h"

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
    setPosition(getPosition() + direction);
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