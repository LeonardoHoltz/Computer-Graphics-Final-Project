#include "GPUData.h"

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
GLuint Textures[NumTextures];

void LoadObject() {
	GLfloat vertices[NumVertices][2] = {
		{ -0.9f, -0.9f }, { 0.9f, -0.9f }, { -0.9f, 0.9f },  // Triangle 1
		{ -0.9f,  0.9f }, { 0.9f, -0.9f }, {  0.9f, 0.9f }   // Triangle 2
	};

	GLfloat textCoord[NumVertices][2] = {
		{ 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f },  // Triangle 1
		{ 0.0f, 1.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }   // Triangle 2
	};

	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[LenticularObjectVAO]);

	glGenBuffers(NumBuffers, Buffers);

	// Bind buffer for the vertices positions
	SetBufferFor2DData(VerticesPositionsBuffer, vertices, NumVertices, vPosition);

	// Bind buffer for the vertices texture coordinates
	SetBufferFor2DData(VerticesTextCoordinatesBuffer, textCoord, NumVertices, vTextCoord);
}


void SetBufferFor2DData(GLuint bufferID, GLfloat (*dataArray)[2], int nrVertices,  GLuint vertexAttribute) {
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[bufferID]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(dataArray) * nrVertices, dataArray, GL_STATIC_DRAW);
	glVertexAttribPointer(vertexAttribute, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(vertexAttribute);
}