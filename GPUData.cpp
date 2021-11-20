#include "GPUData.h"

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
GLuint Textures[NumTextures];

void LoadObject() {
	GLfloat vertices[NumVertices][2] = {
		{ -1.0f, -1.0f }, { 1.0f, -1.0f }, { -1.0f, 1.0f },  // Triangle 1
		{ -1.0f,  1.0f }, { 1.0f, -1.0f }, {  1.0f, 1.0f }   // Triangle 2
	};

	GLfloat textCoord[NumVertices][2] = {
		{ 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f },  // Triangle 1
		{ 0.0f, 1.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }   // Triangle 2
	};

	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[LenticularObjectVAO]);

	glGenBuffers(NumBuffers, Buffers);

	// Bind buffer for the vertices positions
	SetBufferFor2DData(VerticesPositionsBuffer, vertices, vPosition);

	// Bind buffer for the vertices texture coordinates
	SetBufferFor2DData(VerticesTextCoordinatesBuffer, textCoord, vTextCoord);
}


void SetBufferFor2DData(GLuint bufferID, GLfloat (*dataArray)[2], GLuint vertexAttribute) {
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[bufferID]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(dataArray), dataArray, GL_STATIC_DRAW);
	glVertexAttribPointer(vertexAttribute, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(vertexAttribute);
}