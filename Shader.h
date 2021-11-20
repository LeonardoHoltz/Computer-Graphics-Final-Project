#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

typedef struct {
    GLenum       type;
    const char* filename;
    GLuint       shader;
} ShaderInfo;

extern GLuint LenticularObjectShader;

void defineShaders();
static const GLchar* ReadShader(const char* filename);
GLuint LoadShaders(ShaderInfo* shaders);
