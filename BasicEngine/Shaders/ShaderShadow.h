#pragma once
#include "../PCH.h"

namespace BasicEngine
{
	namespace Shaders
	{
		class ShaderShadow : public IShader
		{
		public:
			ShaderShadow(GLuint program);
			virtual void configureShader(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
			void setDepthMap(GLuint depthMap);
			void setLightSpaceMatrix(glm::mat4& lightSpaceMatrix);

		private:
			GLuint depthMap;
			glm::mat4 lightSpaceMatrix;
		};
	}
}