#pragma once

#include <glad/glad.h>
#include <iostream>

const int NumVertices = 6;

enum VAO_IDs { LenticularObjectVAO, NumVAOs };
enum Buffer_IDs { VerticesPositionsBuffer, VerticesTextCoordinatesBuffer, NumBuffers_ };
enum Attrib_IDs { vPosition = 0, vTextCoord = 1 };
enum Texture_IDs { LenticularTexture1, LenticularTexture2, NumTextures };

extern GLuint VAOs[NumVAOs];
extern GLuint Buffers[NumBuffers_];
extern GLuint Textures[NumTextures];


void LoadObject();

/// <summary>
/// Binds a buffer for a data array and links the vertex attribute
/// </summary>
/// <param name="bufferID">ID of the buffer to be binded.</param>
/// <param name="dataArray">Array that contains the data to be used in a buffer.</param>
/// <param name="nrVertices">Number of vertices that in the dataArray.</param>
/// <param name="vertexAttribute">The ID of the vertex attribute to be used in the shader</param>
void SetBufferFor2DData(GLuint bufferID, GLfloat(*dataArray)[2], int nrVertices, GLuint vertexAttribute);
