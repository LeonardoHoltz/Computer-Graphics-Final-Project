#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "input.h"

void SetCallbacks(GLFWwindow* window);
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
