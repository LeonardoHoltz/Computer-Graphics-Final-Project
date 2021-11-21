
#include "Camera.h"
#include "BufferClear.h"
#include "Callbacks.h"
#include "Shader.h"
//#include "GPUData.h"
#include "Texture.h"
#include "Input.h"
#include "Model.h"
#include "Scene.h"
#include "GlintProgram.h"
#include "LenticularProgram.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/transform.hpp>

void SetupGLFW();
void SetupVariables();

glm::mat4 ViewMatrix;
glm::mat4 ModelMatrix;
glm::mat4 ProjectionMatrix;

float HFov, VFov, nearPlane, farPlane;

Scene g_CurrentScene;
Glints_GPUProgram glint_program;
Lenticular_GPUProgram lenticularEffectProgram;

void Load();

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

	Load();

	float color[4] = { 1.0f, 0.2f, 0.8f, 1.0f };
	glUniform4fv(glint_program.color_uniform, 1, color);

	SetupVariables();

	ModelMatrix = glm::mat4(1.0);

	g_Cam.SetCameraVelocity(0.001f);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		if (g_Input.GetKeyState(GLFW_KEY_ESCAPE).is_pressed)
			glfwSetWindowShouldClose(window, GL_TRUE);

		g_Cam.UpdateCamera();
		ViewMatrix = g_Cam.View();
		ProjectionMatrix = g_Cam.Projection(HFov, VFov, nearPlane, farPlane);

		lenticularEffectProgram.Use();
		lenticularEffectProgram.SetTextureUniforms();
		lenticularEffectProgram.SetMatrixUniforms(ViewMatrix, ProjectionMatrix, ModelMatrix);

		ClearScreenBuffers();
		g_CurrentScene.DrawSceneObject("plane");


		glfwSwapBuffers(window);
		g_Input.Update();
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void Load() {
	glint_program.Create({
			{ GL_VERTEX_SHADER, "GlintShader.vert" },
			{ GL_FRAGMENT_SHADER, "GlintShader.frag" },
		});

	lenticularEffectProgram.Create({
			{ GL_VERTEX_SHADER, "LenticularShader.vert" },
			{ GL_FRAGMENT_SHADER, "LenticularShader.frag" },
		});

	CreateTextures();

	ObjModel bunny = ObjModel("Models/bunny.obj");
	ObjModel cube = ObjModel("Models/cube.obj");
	ObjModel plane = ObjModel("Models/plane.obj");

	g_CurrentScene.AddModelToScene(bunny);
	g_CurrentScene.AddModelToScene(cube);
	g_CurrentScene.AddModelToScene(plane);
}

void SetupGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void SetupVariables()
{
	HFov = 90.0f;
	VFov = 50.0f;
	nearPlane = 0.5f;
	farPlane = 5000.0f;
}
