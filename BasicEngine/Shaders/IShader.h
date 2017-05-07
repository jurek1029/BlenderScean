#pragma once
#include <glew/glew.h>
#include <freeglut/freeglut.h>
#include <glm\glm.hpp>

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