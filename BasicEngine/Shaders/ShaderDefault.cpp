#include "ShaderDefault.h"

using namespace BasicEngine::Shaders;

ShaderDefault::ShaderDefault(GLuint program) : IShader(program) {}

void ShaderDefault::configureShader(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{
	glUniform3f(glGetUniformLocation(program, "light.position"), 0, 8, 0);
	glUniform3f(glGetUniformLocation(program, "light.ambient"), 0.4f, 0.4f, 0.4f);
	glUniform3f(glGetUniformLocation(program, "light.diffuse"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(program, "light.specular"), 1.0f, 1.0f, 1.0f);

	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &viewMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projectionMatrix[0][0]);
}