#include "../PCH.h"

using namespace BasicEngine::Shaders;

ShaderShadow::ShaderShadow(GLuint program) :IShader(program) {}

void ShaderShadow::configureShader(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{
	glUniform3f(glGetUniformLocation(program, "light.position"), 0, 8, 0);
	glUniform3f(glGetUniformLocation(program, "light.ambient"), 0.4f, 0.4f, 0.4f);
	glUniform3f(glGetUniformLocation(program, "light.diffuse"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(program, "light.specular"), 1.0f, 1.0f, 1.0f);

	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &viewMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projectionMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "lightSpaceMatrix"), 1, false, &lightSpaceMatrix[0][0]);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	unsigned int textureLocation = glGetUniformLocation(program, "shadowMap");
	glUniform1i(textureLocation, 1);

}

void ShaderShadow::setDepthMap(GLuint _depthMap) { depthMap = _depthMap; }
void ShaderShadow::setLightSpaceMatrix(glm::mat4& _lightSpaceMatrix) { lightSpaceMatrix = _lightSpaceMatrix; }