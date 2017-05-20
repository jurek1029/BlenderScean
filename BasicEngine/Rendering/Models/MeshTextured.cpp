#include "../../PCH.h"

using namespace BasicEngine::Rendering;
using namespace Models;

MeshTextured::MeshTextured() {}

MeshTextured::~MeshTextured() {}

void MeshTextured::Update()
{

}

void MeshTextured::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, (*textures.begin()).second);
	unsigned int textureLocation = glGetUniformLocation(program->program, "texture1");
	glUniform1i(textureLocation, 0);

	glUniform3f(glGetUniformLocation(program->program, "material.ambient"), 0.1f, 0.1f, 0.1f);
	glUniform3f(glGetUniformLocation(program->program, "material.diffuse"), 0.5f, 0.5f, 0.5f);
	glUniform3f(glGetUniformLocation(program->program, "material.specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(program->program, "material.shininess"), 0.0f);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indicesLength, GL_UNSIGNED_INT, 0);
}

