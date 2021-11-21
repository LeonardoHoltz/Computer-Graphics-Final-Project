#include "GlintProgram.h"

void Glints_GPUProgram::MapUniforms() {
	color_uniform = glGetUniformLocation(program_id, "color");
	mvp_uniform = glGetUniformLocation(program_id, "model_view_proj");
}