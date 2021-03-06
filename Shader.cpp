#include "Shader.h"

void GPUProgram::Create(std::vector<ShaderInfo> shader_files) {
    this->shader_files = shader_files;

    Compile();

    if (program_id != 0)
        glDeleteProgram(program_id);
    program_id = glCreateProgram();

    Link();

    MapUniforms();
}

void GPUProgram::Compile() {
    for (auto& shader : shader_files) {

        GLuint shader_id = glCreateShader(shader.type);

        try {
            std::string file_string;

            std::ifstream file;
            file.exceptions(std::ifstream::failbit);
            file.open(shader.filename);

            std::stringstream file_stream;
            file_stream << file.rdbuf();
            file_string = file_stream.str();

            const char* shader_string = file_string.c_str();
            const int   shader_string_length = static_cast<int>(file_string.length());

            glShaderSource(shader_id, 1, &shader_string, &shader_string_length);
            // delete [] shader_string;
            glCompileShader(shader_id);

            int compiled_status = PrintGLSL_Logs(shader.filename, shader_id);

            if (!compiled_status) {
                throw std::runtime_error("Shader compilation failed");
            }
            else {
                std::cout << "Shader successfully compiled : " << shader.filename << std::endl;
            }
        }
        catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            glDeleteShader(shader_id);
            shader_id = 0;
        }

        shader.shader = shader_id;
    }
}

void GPUProgram::Link() {
    for (auto it : shader_files)
        glAttachShader(program_id, it.shader);

    glLinkProgram(program_id);

    GLint linked_ok = GL_FALSE;
    glGetProgramiv(program_id, GL_LINK_STATUS, &linked_ok);

    linked = linked_ok;
    if (linked_ok == GL_FALSE)
    {
        GLint log_length = 0;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);

        GLchar* log = new GLchar[log_length];

        glGetProgramInfoLog(program_id, log_length, &log_length, log);

        std::cerr << "ERROR: OpenGL linking of program failed.\n";
        std::cerr << "== Start of link log\n";
        std::cerr << log;
        std::cerr << "\n== End of link log\n";
        std::cerr << std::endl;

        delete[] log;

        for (auto& it : shader_files) {
            glDeleteShader(it.shader);
            it.shader = 0;
        }
        program_id = 0;
    }
}

void GPUProgram::Use() {
    if (program_id <= 0 || !linked)
        std::cerr << "Shader has not been linked" << std::endl;
    glUseProgram(program_id);
}

int PrintGLSL_Logs(const char* filename, unsigned int shader_id)
{
    int compiled_ok;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled_ok);

    int log_length = 0;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);

    char* log = new GLchar[log_length];
    glGetShaderInfoLog(shader_id, log_length, &log_length, log);

    if (log_length != 0)
    {
        if (!compiled_ok) {
            std::clog << "ERROR: ";
        }
        else {
            std::clog << "WARNING: ";
        }
        std::clog << "OpenGL compilation of \"";
        std::clog << filename;
        std::clog << "\" failed.\n";
        std::clog << "== Start of compilation log\n";
        std::clog << log;
        std::clog << "== End of compilation log\n";
        std::clog << std::endl;
    }

    delete[] log;
    return compiled_ok;
}