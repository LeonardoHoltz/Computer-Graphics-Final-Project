#pragma once

#include <glad/glad.h>

const int NumVertices = 6;

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { VerticesPositionsBuffer, VerticesTextCoordinatesBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0, vTextCoord = 1 };

GLuint  VAOs[NumVAOs];
GLuint  Buffers[2];

void LoadObject();

/// <summary>
/// Binds a buffer for a data array and links the vertex attribute
/// </summary>
/// <param name="bufferID">ID of the buffer to be binded.</param>
/// <param name="dataArray">Array that contains the data to be used in a buffer.</param>
/// <param name="vertexAttribute">The ID of the vertex attribute to be used in the shader</param>
void SetBufferFor2DData(GLuint bufferID, GLfloat (*dataArray)[2], GLuint vertexAttribute);