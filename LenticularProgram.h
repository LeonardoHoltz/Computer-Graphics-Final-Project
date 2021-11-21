#pragma once
#include "Shader.h"

class Lenticular_GPUProgram : public GPUProgram {
public:
	GLuint viewMatrixUniform;
	GLuint modelMatrixUniform;
	GLuint projectionMatrixUniform;
	GLuint Texture0Uniform;
	GLuint Texture1Uniform;

	void MapUniforms();
	void SetTextureUniforms();
	void SetMatrixUniforms(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat4 modelMatrix);
};

