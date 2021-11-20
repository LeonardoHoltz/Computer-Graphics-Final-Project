#include "GlintProgram.h"

void Glints_GPUProgram::MapUniforms() {
	color_uniform = glGetUniformLocation(program_id, "color");
}