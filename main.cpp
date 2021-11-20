
#include "Camera.h"
#include "BufferClear.h"
#include "Callbacks.h"
#include "Shader.h"
#include "GPUData.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
	defineShaders();
	
	glfwInit();
	gladLoadGL();

	glUseProgram(LenticularObjectShader);

	LoadObject();

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics Final Project", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	SetCallbacks(window);

	while (!glfwWindowShouldClose(window))
	{
		ClearScreenBuffers();
		glDrawArrays(GL_TRIANGLES, 0, NumVertices);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}