#pragma once

#include "Shader.h"

class Glints_GPUProgram : public GPUProgram {
public:
    GLint model_uniform; 
    GLint mvp_uniform; 

    GLint light_i_uniform; 
    GLint light_pos_uniform; 

    GLint dict_alpha_uniform;
    GLint dict_n_uniform; 
    GLint dict_nlevels_uniform; 
    GLint dict_pyramid0size_uniform; 
    GLint dict_texture_uniform; 

    GLint camera_pos_uniform; 

    GLint microfacet_area_uniform; 
    GLint max_anisotropy_uniform; 
    GLint material_lmicrofacet_uniform; 
    GLint material_alpha_x_uniform; 
    GLint material_alpha_y_uniform; 

    void MapUniforms();
};
