#include "Scene.h"

void Scene::AddModelToScene(ObjModel model) {
    GLuint vertex_array_object_id;
    glGenVertexArrays(1, &vertex_array_object_id);
    glBindVertexArray(vertex_array_object_id);

    std::vector<GLuint> indices;
    std::vector<float>  model_coefficients;
    std::vector<float>  normal_coefficients;
    std::vector<float>  texture_coefficients;

    for (auto &shape : model.shapes) {
        size_t num_triangles = shape.mesh.num_face_vertices.size();
        for (size_t triangle = 0; triangle < num_triangles; ++triangle) {
            assert(shape.mesh.num_face_vertices[triangle] == 3);
            for (size_t vertex = 0; vertex < 3; ++vertex) {
                tinyobj::index_t idx = shape.mesh.indices[3 * triangle + vertex];

                indices.push_back(3 * triangle + vertex);

                const float vx = model.attrib.vertices[3 * idx.vertex_index + 0];
                const float vy = model.attrib.vertices[3 * idx.vertex_index + 1];
                const float vz = model.attrib.vertices[3 * idx.vertex_index + 2];

                model_coefficients.push_back(vx); // X
                model_coefficients.push_back(vy); // Y
                model_coefficients.push_back(vz); // Z
                model_coefficients.push_back(1.0f); // W

                if (idx.normal_index != -1)
                {
                    const float nx = model.attrib.normals[3 * idx.normal_index + 0];
                    const float ny = model.attrib.normals[3 * idx.normal_index + 1];
                    const float nz = model.attrib.normals[3 * idx.normal_index + 2];
                    normal_coefficients.push_back(nx); // X
                    normal_coefficients.push_back(ny); // Y
                    normal_coefficients.push_back(nz); // Z
                    normal_coefficients.push_back(0.0f); // W
                }

                if (idx.texcoord_index != -1)
                {
                    const float u = model.attrib.texcoords[2 * idx.texcoord_index + 0];
                    const float v = model.attrib.texcoords[2 * idx.texcoord_index + 1];
                    texture_coefficients.push_back(u);
                    texture_coefficients.push_back(v);
                }
            }
        }
    }
    SceneObject theobject;
    theobject.name = model.shapes[0].name;
    theobject.first_index = 0;
    theobject.num_indices = indices.size();
    theobject.rendering_mode = GL_TRIANGLES;
    theobject.vao_id = vertex_array_object_id;

    this->SetArrayBuffer(&theobject, VerticesBuffer, vertexLocation, 4, model_coefficients.size(), model_coefficients.data());
    if (!normal_coefficients.empty())
        this->SetArrayBuffer(&theobject, NormalsBuffer,  normalLocation,   4, normal_coefficients.size(), normal_coefficients.data());
    if (!texture_coefficients.empty())
        this->SetArrayBuffer(&theobject, TextureCoordBuffer, textCoordLocation, 2, texture_coefficients.size(), texture_coefficients.data());

    GLuint indices_id;
    glGenBuffers(1, &indices_id);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    theobject.indices_id = indices_id;

    this->objects[theobject.name] = theobject;

    glBindVertexArray(0);

}

void Scene::SetArrayBuffer(SceneObject *obj, GLuint bufferID, GLuint location, GLint dimensions, int data_length,  GLfloat *data) {
    glGenBuffers(1, &obj->vbo_ids[bufferID]);
    glBindBuffer(GL_ARRAY_BUFFER, obj->vbo_ids[bufferID]);
    glBufferData(GL_ARRAY_BUFFER, data_length * sizeof(GLfloat), data, GL_STATIC_DRAW);
    glVertexAttribPointer(location, dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Scene::DrawSceneObject(const char* model_name) {
    if (!objects.count(model_name)) {
        std::cerr << "object not found: " << model_name << std::endl;
        return;
    }
    
    glBindVertexArray(objects[model_name].vao_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objects[model_name].indices_id);

    glDrawElements(
        objects[model_name].rendering_mode,
        objects[model_name].num_indices,
        GL_UNSIGNED_INT,
        (void*)0
    );

    glBindVertexArray(0);
}

