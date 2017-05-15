#pragma once
#include <glew\glew.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include "soil\SOIL.h"


namespace BasicEngine
{
	namespace Managers
	{
		class TextureManager
		{
		public:
			TextureManager();
			~TextureManager();

			GLuint GetTexture(std::string name);
			GLuint GetCubemapTexture(std::string name, std::vector<const GLchar*> faces);
		
		private:
			std::map<std::string, GLuint> textures;
		};
	}
}