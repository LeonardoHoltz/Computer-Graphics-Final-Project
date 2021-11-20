#pragma once
#include "Shader.h"
class Lenticular_GPUProgram : public GPUProgram {
public:
	GLuint viewMatrixUniform;
	GLuint modelMatrixUniform;
	GLuint projectionMatrixUniform;

	void MapUniforms();
};

