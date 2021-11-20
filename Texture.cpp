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

void CreateTexture() {
	glGenTextures(NumTextures, Textures);
	glBindTexture(GL_TEXTURE_2D, Textures[LenticularTexture1]);
	Texture image = LoadNewTexture("GRU.jpg");
	glActiveTexture(GL_TEXTURE1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.getWidth(), image.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.getData());
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(image.getData());
}