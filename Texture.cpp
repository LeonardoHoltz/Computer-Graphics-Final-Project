#include "Texture.h"

#define TINYEXR_IMPLEMENTATION
#include "tinyexr.h"

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
	}
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, Textures[LenticularTexture2]);
	Texture image2 = LoadNewTexture(Images[1]);
	if (image2.getData())
	{
		std::cout << "Image " << Images[1] << " was loaded successfully." << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image2.getWidth(), image2.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image2.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(image1.getData());
	stbi_image_free(image2.getData());
}


GLuint loadDictionary(const unsigned int nlevels, const GLsizei ndists)
{
	GLuint texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_1D_ARRAY, texID);

	GLint width;
	GLint height;
	GLsizei layerCount = ndists * nlevels;
	GLsizei mipLevelCount = 1;

	std::string texName = "dictionary/dict_16_192_64_0p5_0p02_0000_0000.exr";
	float* data;
	const char** err = nullptr;
	bool ret = LoadEXR(&data, &width, &height, texName.c_str(), err);
	if (!ret) {
		std::cerr << "Error loading exr file: " << texName << std::endl;
		exit(-1);
	}

	glTexImage2D(GL_TEXTURE_1D_ARRAY, 0, GL_RGB16F, width, layerCount, 0, GL_RGBA, GL_FLOAT, data);
	glTexSubImage2D(GL_TEXTURE_1D_ARRAY, 0, 0, 0, width, 1, GL_RGBA, GL_FLOAT, data);
	
	//free(data);

	for (int l = 0; l < nlevels; ++l) {
		std::cout << l << std::endl;
		std::string index_level;
		if (l < 10)
			index_level = "000" + std::to_string(l);
		else if (l < 100)
			index_level = "00" + std::to_string(l);
		else if (l < 1000)
			index_level = "0" + std::to_string(l);
		else
			index_level = std::to_string(l);

		for (int i = 0; i < ndists; i++) {

			if (l == 0 && i == 0) continue;

			std::string index_dist;
			if (i < 10)
				index_dist = "000" + std::to_string(i);
			else if (i < 100)
				index_dist = "00" + std::to_string(i);
			else if (i < 1000)
				index_dist = "0" + std::to_string(i);
			else
				index_dist = std::to_string(i);

			texName = "dictionary/dict_16_192_64_0p5_0p02_" + index_dist + "_" + index_level + ".exr";
			bool ret = LoadEXR(&data, &width, &height, texName.c_str(), err);
			if (!ret) {
				exit(-1);
			}
			glTexSubImage2D(GL_TEXTURE_1D_ARRAY, 0, 0, l * ndists + i, width, 1, GL_RGBA, GL_FLOAT, data);
			
			//free(data);
		}
	}

	glTexParameteri(GL_TEXTURE_1D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_1D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

	return texID;
}