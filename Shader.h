#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

typedef struct {
    GLenum       type;
    const char* filename;
    GLuint       shader;
} ShaderInfo;

extern GLuint LenticularObjectShader;

void defineShaders();
static const GLchar* ReadShader(const char* filename);
GLuint LoadShaders(ShaderInfo* shaders);


class GPUProgram {
private:
    std::vector<ShaderInfo> shader_files;
    void Compile();
    void Link();
    virtual void MapUniforms() = 0;

public:
    GLuint program_id;
    bool linked = false;

    void Create(std::vector<ShaderInfo> shader_files);
    void Use();
};

int PrintGLSL_Logs(const char* filename, unsigned int shader_id);
