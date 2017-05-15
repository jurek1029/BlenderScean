#include "ShaderSkyBox.h"

using namespace BasicEngine::Shaders;

ShaderSkyBox::ShaderSkyBox(GLuint program) : IShader(program) {}

void ShaderSkyBox::configureShader(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{
	glm::mat4 view = glm::mat4(glm::mat3(viewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, false, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, false, &projectionMatrix[0][0]);
}