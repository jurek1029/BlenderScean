#pragma once
#include "../PCH.h"

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