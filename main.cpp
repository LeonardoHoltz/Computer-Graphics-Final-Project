#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Callbacks.h"
#include "BufferClear.h"

int main()
{
	glfwInit();
	gladLoadGL();

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
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}