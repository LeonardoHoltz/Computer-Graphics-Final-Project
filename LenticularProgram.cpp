#include "LenticularProgram.h"

void Lenticular_GPUProgram::MapUniforms() {
	viewMatrixUniform = glGetUniformLocation(program_id, "view");
	modelMatrixUniform = glGetUniformLocation(program_id, "model");
	projectionMatrixUniform = glGetUniformLocation(program_id, "projection");
}