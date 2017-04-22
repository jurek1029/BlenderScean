#pragma once
#include <glew\glew.h>
#include <stdlib.h>
#include <map>
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
		
		private:
			std::map<std::string, GLuint> textures;
		};
	}
}