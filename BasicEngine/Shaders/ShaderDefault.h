#pragma once
#include "../PCH.h"

namespace BasicEngine
{
	namespace Shaders
	{
		class ShaderDefault : public IShader
		{
		public:
			ShaderDefault(GLuint program);
			virtual void configureShader(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
		};
	}
}