#pragma once

#include "Shader.h"

class Glints_GPUProgram : public GPUProgram {
public:
    GLint color_uniform;
    GLint mvp_uniform;

    void MapUniforms();
};
