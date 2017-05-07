#pragma once
#include "IShader.h"

namespace BasicEngine
{
	namespace Shaders
	{
		class ShaderDebug : public IShader
		{
		public :
			ShaderDebug(GLuint program);
			virtual void configureShader(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
		};
	}
}