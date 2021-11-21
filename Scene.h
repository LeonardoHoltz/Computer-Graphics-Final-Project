#pragma once

#include <string>
#include <map>
#include <vector>
#include <glad/glad.h>

#include "Model.h"

enum Buffers { VerticesBuffer, NormalsBuffer, TextureCoordBuffer, NumBuffers };
enum AttribLocations { vertexLocation = 0, normalLocation = 1, textCoordLocation = 2 };

struct SceneObject
{
    std::string  name;
    GLsizei      first_index;
    GLsizei      num_indices;
    GLenum       rendering_mode;
    GLuint       vao_id;
    GLuint       indices_id;
    GLuint       vbo_ids[NumBuffers];
};

class Scene {
private:
	std::map<std::string, SceneObject> objects;
	void SetArrayBuffer(SceneObject* obj, GLuint bufferID, GLuint location, GLint dimensions, int data_length, GLfloat* data);

public:
	void AddModelToScene(ObjModel model);
	void DrawSceneObject(const char* model_name);
};
