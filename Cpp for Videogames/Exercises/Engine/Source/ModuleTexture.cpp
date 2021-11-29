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

bool ModuleTexture::CleanUp() {


	return true;
}