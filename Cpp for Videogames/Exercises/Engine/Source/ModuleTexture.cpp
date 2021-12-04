#include "ModuleTexture.h"

ModuleTexture::ModuleTexture()
{
}

ModuleTexture::~ModuleTexture()
{
}

bool ModuleTexture::Init() {
	assert(ilGetInteger(IL_VERSION_NUM) == IL_VERSION);
	ilInit();

	return true;
}

unsigned ModuleTexture::LoadTexture(const char* texturePath) {
	ILuint textureId;

	ilGenImages(1, &textureId);
	ilBindImage(textureId);
	if (!ilLoadImage(texturePath)) {
		std::cout << "Error loading texture" << std::endl;
		return 0;
	}
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

	return textureId;
}

Texture ModuleTexture::Load(const char* texturePath) {
	unsigned texId = LoadTexture(texturePath);
	Texture texture(texId, texturePath);

	if (texId != 0) {
		glGenTextures(1, &texture.id);
		glBindTexture(GL_TEXTURE_2D, texture.id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(	GL_TEXTURE_2D, 0, GL_RGB, texture.width = ilGetInteger(IL_IMAGE_WIDTH),
						texture.height = ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGB, GL_UNSIGNED_BYTE, ilGetData());

		texture.isLoaded = true;
		ilDeleteImages(1, &texId);
	}
	else {
		LOG("Error loading texture image from %s: %s", texturePath, ilGetError());
	}
	
	return texture;
}

bool ModuleTexture::CleanUp() {
	ilShutDown();
	return true;
}