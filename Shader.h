#pragma once
#include <glad/glad.h>
#include <iostream>

typedef struct {
    GLenum       type;
    const char* filename;
    GLuint       shader;
} ShaderInfo;

static const GLchar* ReadShader(const char* filename);
GLuint LoadShaders(ShaderInfo* shaders);
