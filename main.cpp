
#include "Camera.h"
#include "BufferClear.h"
#include "Callbacks.h"
#include "Shader.h"
#include "GPUData.h"
#include "Texture.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void SetupGLFW();

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
	SetCallbacks(window);

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
		ClearScreenBuffers();
		glBindVertexArray(VAOs[LenticularObjectVAO]);
		glDrawArrays(GL_TRIANGLES, 0, NumVertices);

		glfwSwapBuffers(window);
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
