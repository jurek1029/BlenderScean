#include "ShaderDebug.h"

using namespace BasicEngine::Shaders;

ShaderDebug::ShaderDebug(GLuint program): IShader(program) {}

void ShaderDebug::configureShader(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &viewMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projectionMatrix[0][0]);
}