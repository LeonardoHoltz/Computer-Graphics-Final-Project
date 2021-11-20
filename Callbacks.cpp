#include "Callbacks.h"



void SetCallbacks(GLFWwindow* window) {
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetCursorPosCallback(window, CursorPosCallback);
	glfwSetScrollCallback(window, ScrollCallback);
}

//void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) { }

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mod)
{
	g_Input.KeyCallback(key, action, mod);
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	g_Input.KeyCallback(button, action, mods);
}

void CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	g_Input.cursor_state.xvalue = xpos;
	g_Input.cursor_state.yvalue = ypos;
	g_Input.cursor_changed = true;
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	g_Input.scroll_state.xvalue = xoffset;
	g_Input.scroll_state.yvalue = yoffset;
	g_Input.scroll_changed = true;
}