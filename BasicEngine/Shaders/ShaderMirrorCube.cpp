#include "../PCH.h"

using namespace BasicEngine::Shaders;

ShaderMirrorCube::ShaderMirrorCube(GLuint program) : IShader(program) {}

void ShaderMirrorCube::configureShader(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{
	glm::mat4 model = glm::mat4();
	glUniform3fv(glGetUniformLocation(program, "cameraPos"), 1, &BasicEngine::Controls::CameraFPS::eyeVector[0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, false, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, false, &viewMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, false, &projectionMatrix[0][0]);
}