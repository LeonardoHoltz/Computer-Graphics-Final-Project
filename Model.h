#pragma once

#include <iostream>

#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/detail/func_geometric.hpp>

#include "tiny_obj_loader.h"

class ObjModel {
public:
    tinyobj::attrib_t                 attrib;
    std::vector<tinyobj::shape_t>     shapes;
    std::vector<tinyobj::material_t>  materials;

    ObjModel(const char* filename, const char* basepath = NULL, bool triangulate = true);
    void ComputeNormals();
};
