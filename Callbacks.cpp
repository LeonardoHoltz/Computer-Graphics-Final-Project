#include "Callbacks.h"

void SetCallbacks(GLFWwindow* window) {
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}