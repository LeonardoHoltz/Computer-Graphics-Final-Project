
#include "Camera.h"
#include "BufferClear.h"
#include "Callbacks.h"
#include "Shader.h"
#include "GPUData.h"
#include "Texture.h"
#include "Input.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Input g_Input;

void SetupGLFW();

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

int main()
{
	// All the GLFW window procedements needed to be done before initiate the GLAD GL loader

	SetupGLFW();

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics Final Project", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	//SetCallbacks(window);

	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetCursorPosCallback(window, CursorPosCallback);
	glfwSetScrollCallback(window, ScrollCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	defineShaders();

	glUseProgram(LenticularObjectShader);

	LoadObject();
	CreateTextures();

	while (!glfwWindowShouldClose(window))
	{
		if (g_Input.GetKeyState(GLFW_KEY_ESCAPE).is_pressed)
			glfwSetWindowShouldClose(window, GL_TRUE);

		ClearScreenBuffers();
		glBindVertexArray(VAOs[LenticularObjectVAO]);
		glDrawArrays(GL_TRIANGLES, 0, NumVertices);

		glfwSwapBuffers(window);
		g_Input.Update();
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void SetupGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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