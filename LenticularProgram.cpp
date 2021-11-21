#include "LenticularProgram.h"

void Lenticular_GPUProgram::MapUniforms() {
	viewMatrixUniform = glGetUniformLocation(program_id, "view");
	modelMatrixUniform = glGetUniformLocation(program_id, "model");
	projectionMatrixUniform = glGetUniformLocation(program_id, "projection");

	Texture0Uniform = glGetUniformLocation(program_id, "tex0");
	Texture1Uniform = glGetUniformLocation(program_id, "tex1");
}

void Lenticular_GPUProgram::SetTextureUniforms() {
	glUniform1i(Texture0Uniform, 0);
	glUniform1i(Texture1Uniform, 1);
}

void Lenticular_GPUProgram::SetMatrixUniforms(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat4 modelMatrix) {
	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}