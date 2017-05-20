#include "../PCH.h"

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

GLuint TextureManager::GetCubemapTexture(std::string name ,std::vector<const GLchar*> faces)
{
	auto tex = textures.find(name);
	if (tex == textures.end())
	{
		
		GLuint textureID = SOIL_load_OGL_cubemap(faces[0], faces[1], faces[2], faces[3], faces[4], faces[5], SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
		/*glGenTextures(1, &textureID);
		glActiveTexture(GL_TEXTURE0);

		int width, height;
		unsigned char* image;

		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
		for (GLuint i = 0; i < faces.size(); i++)
		{
			image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		*/
		textures[name.c_str()] = textureID;
		return textureID;
	}
	else
		return (*tex).second;
}