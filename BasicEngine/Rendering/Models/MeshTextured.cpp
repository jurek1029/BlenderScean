#include "MeshTextured.h"
using namespace BasicEngine::Rendering;
using namespace Models;

MeshTextured::MeshTextured()
{
}

MeshTextured::~MeshTextured()
{
}

void MeshTextured::Update()
{

}

void MeshTextured::Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{
	glUseProgram(program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, (*textures.begin()).second);
	unsigned int textureLocation = glGetUniformLocation(program, "texture1");
	glUniform1i(textureLocation, 0);

	//glUniform3f(glGetUniformLocation(program, "rotation"), rotation_sin.x, rotation_sin.y, rotation_sin.z);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &viewMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projectionMatrix[0][0]);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indicesLength, GL_UNSIGNED_INT, 0);
}

