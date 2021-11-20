#pragma once

#include "stb_image.h"
#include "GPUData.h"

class Texture
{
private:
	int _width, _height, _nrChannels;
	unsigned char* _data;
public:

	Texture(int width, int height, int nrChannels, unsigned char* data);

	int getWidth();
	int getHeight();
	int getNrChannels();
	unsigned char* getData();

	void setWidth(int width);
	void setHeight(int height);
	void setNrChannels(int nrChannels);
	void setData(unsigned char* data);
};

void CreateTextures();
Texture LoadNewTexture(const char* fileName);