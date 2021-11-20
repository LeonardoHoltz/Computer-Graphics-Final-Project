#include "Texture.h"

Texture::Texture(int width, int height, int nrChannels, unsigned char* data) {
	setWidth(width);
	setHeight(height);
	setNrChannels(nrChannels);
	setData(data);
}

int Texture::getWidth() {
	return _width;
}

int Texture::getHeight() {
	return _height;
}

int Texture::getNrChannels() {
	return _nrChannels;
}

unsigned char* Texture::getData() {
	return _data;
}

void Texture::setWidth(int width) {
	_width = width;
}

void Texture::setHeight(int height) {
	_height = height;
}

void Texture::setNrChannels(int nrChannels) {
	_nrChannels = nrChannels;
}

void Texture::setData(unsigned char* data) {
	_data = data;
}

Texture LoadNewTexture(const char* fileName) {
	int width, height, nrChannels;
	unsigned char* data;
	data = stbi_load(fileName, &width, &height, &nrChannels, 0);
	Texture newTexture(width, height, nrChannels, data);
	return newTexture;
}

void CreateTextures() {
	glGenTextures(NumTextures, Textures);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Textures[LenticularTexture1]);
	Texture image1 = LoadNewTexture("GRU.jpg");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image1.getWidth(), image1.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image1.getData());
	glGenerateMipmap(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, Textures[LenticularTexture2]);
	Texture image2 = LoadNewTexture("gru delete this.jpg");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image2.getWidth(), image2.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image2.getData());
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(image1.getData());
	stbi_image_free(image2.getData());
}