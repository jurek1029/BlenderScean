#pragma once
#include "../PCH.h"

namespace BasicEngine
{
	namespace Shaders
	{
		class ShaderMirrorCube : public IShader
		{
		public:
			ShaderMirrorCube(GLuint program);
			virtual void configureShader(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
		};
	}
}