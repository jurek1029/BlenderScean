#include "IShader.h"

using namespace BasicEngine::Shaders;

IShader::IShader(GLuint program):program(program){}

void IShader::configureShader(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{

}