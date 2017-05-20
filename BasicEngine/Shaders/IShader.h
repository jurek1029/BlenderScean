#pragma once
#include "../PCH.h"

namespace BasicEngine
{
	namespace Shaders
	{
		class IShader
		{
		public:
				IShader(GLuint program);
				virtual void configureShader(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
				GLuint program;
		};
	}
}