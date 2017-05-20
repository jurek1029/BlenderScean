#include "../../PCH.h"

using namespace BasicEngine::Rendering;
using namespace Models;

MeshFlat::MeshFlat()
{
}

MeshFlat::~MeshFlat()
{
}

void MeshFlat::Update()
{

}

void MeshFlat::DrawDebug()
{
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

void MeshFlat::Draw()
{
	glUniform3f(glGetUniformLocation(program->program, "material.ambient"), diffuseColor.x*0.2f, diffuseColor.y*0.2f, diffuseColor.z*0.2f);
	glUniform3f(glGetUniformLocation(program->program, "material.diffuse"), diffuseColor.x, diffuseColor.y, diffuseColor.z);
	glUniform3f(glGetUniformLocation(program->program, "material.specular"), specularColor.x, specularColor.y, specularColor.z);
	glUniform1f(glGetUniformLocation(program->program, "material.shininess"), specularColor.w);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

