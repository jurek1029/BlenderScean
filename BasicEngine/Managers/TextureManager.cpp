#include "TextureManager.h"

using namespace BasicEngine::Managers;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

GLuint TextureManager::GetTexture(std::string name)
{
	auto tex = textures.find(name);
	if (tex == textures.end())
	{
		textures[name.c_str()] = SOIL_load_OGL_texture(name.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
		printf("%s\n", SOIL_last_result());
		return textures[name.c_str()];
	}
	else
		return (*tex).second;
}