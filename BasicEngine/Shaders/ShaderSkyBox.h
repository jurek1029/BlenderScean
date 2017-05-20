#pragma once
#include "../PCH.h"

namespace BasicEngine
{
	namespace Shaders
	{
		class ShaderSkyBox : public IShader
		{
		public:
			ShaderSkyBox(GLuint program);
			virtual void configureShader(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
		};
	}
}