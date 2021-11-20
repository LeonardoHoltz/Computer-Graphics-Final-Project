#pragma once

#include <GLFW/glfw3.h>

void SetCallbacks(GLFWwindow* window);
//void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
