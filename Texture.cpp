#include "Texture.h"

std::vector<std::string> Images;

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

Texture LoadNewTexture(std::string filename) {
	int width, height, nrChannels;
	unsigned char* data;
	std::string path = "Images/" + filename;
	const char* filePath = path.c_str();
	data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	Texture newTexture(width, height, nrChannels, data);
	return newTexture;
}

void CreateTextures() {
	glGenTextures(NumTextures, Textures);
	Images.push_back("mandrill.jpg");
	Images.push_back("checker.jpg");

	stbi_set_flip_vertically_on_load(true);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Textures[LenticularTexture1]);
	Texture image1 = LoadNewTexture(Images[0]);
	if (image1.getData())
	{
		std::cout << "Image " << Images[0] << " was loaded successfully." << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image1.getWidth(), image1.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image1.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
		glUniform1i(glGetUniformLocation(LenticularObjectShader, "tex0"), 0);
	}
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, Textures[LenticularTexture2]);
	Texture image2 = LoadNewTexture(Images[1]);
	if (image2.getData())
	{
		std::cout << "Image " << Images[1] << " was loaded successfully." << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image2.getWidth(), image2.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image2.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
		glUniform1i(glGetUniformLocation(LenticularObjectShader, "tex1"), 1);
	}

	stbi_image_free(image1.getData());
	stbi_image_free(image2.getData());
}