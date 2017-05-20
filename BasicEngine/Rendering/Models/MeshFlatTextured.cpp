#include "../../PCH.h"

using namespace BasicEngine::Rendering;
using namespace Models;

MeshFlatTextured::MeshFlatTextured() {}

MeshFlatTextured::~MeshFlatTextured() {}

void MeshFlatTextured::Update()
{

}

void MeshFlatTextured::Draw()
{

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, (*textures.begin()).second);
	unsigned int textureLocation = glGetUniformLocation(program->program, "texture1");
	glUniform1i(textureLocation, 0);

	glUniform3f(glGetUniformLocation(program->program, "material.ambient"), 0.1f, 0.1f, 0.1f);
	glUniform3f(glGetUniformLocation(program->program, "material.diffuse"), 0.8f, 0.8f, 0.8f);
	glUniform3f(glGetUniformLocation(program->program, "material.specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(program->program, "material.shininess"), 0.0f);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}
