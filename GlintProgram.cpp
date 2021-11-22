#include "GlintProgram.h"

void Glints_GPUProgram::MapUniforms() {
	mvp_uniform = glGetUniformLocation(program_id, "MVP");
	model_uniform = glGetUniformLocation(program_id, "ModelMatrix");
	light_i_uniform = glGetUniformLocation(program_id, "Light.L");
	light_pos_uniform = glGetUniformLocation(program_id, "Light.Position");
	dict_alpha_uniform = glGetUniformLocation(program_id, "Dictionary.Alpha");
	dict_n_uniform = glGetUniformLocation(program_id, "Dictionary.N");
	dict_nlevels_uniform = glGetUniformLocation(program_id, "Dictionary.NLevels");
	dict_pyramid0size_uniform = glGetUniformLocation(program_id, "Dictionary.Pyramid0Size");
	dict_texture_uniform = glGetUniformLocation(program_id, "DictionaryTex");
	camera_pos_uniform = glGetUniformLocation(program_id, "CameraPosition");
	microfacet_area_uniform = glGetUniformLocation(program_id, "MicrofacetRelativeArea");
	max_anisotropy_uniform = glGetUniformLocation(program_id, "MaxAnisotropy");
	material_lmicrofacet_uniform = glGetUniformLocation(program_id, "Material.LogMicrofacetDensity");
	material_alpha_x_uniform = glGetUniformLocation(program_id, "Material.Alpha_x");
	material_alpha_y_uniform = glGetUniformLocation(program_id, "Material.Alpha_y");
}