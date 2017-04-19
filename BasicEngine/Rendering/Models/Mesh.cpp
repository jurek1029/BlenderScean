#include "Mesh.h"
using namespace BasicEngine::Rendering;
using namespace Models;

Mesh::Mesh()
{

}

Mesh::~Mesh()
{

}
template < class T >
void Mesh::Create(std::vector<T>& vertices, int mask)
{
	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//std::vector<VertexFormat> vertices;
	std::vector<unsigned int>  indices;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexFormat), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::texture)));
	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);

}
template void Mesh::Create<VertexFormatP>(std::vector<VertexFormatP>& vertices, int mask);
template void Mesh::Create<VertexFormatN>(std::vector<VertexFormatN>& vertices, int mask);
template void Mesh::Create<VertexFormatUV>(std::vector<VertexFormatUV>& vertices, int mask);
template void Mesh::Create<VertexFormatNUV>(std::vector<VertexFormatNUV>& vertices, int mask);

void Mesh::Update()
{

}

void Mesh::Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{
	glUseProgram(program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->GetTexture("Create"));
	unsigned int textureLocation = glGetUniformLocation(program, "texture1");
	glUniform1i(textureLocation, 0);

	//glUniform3f(glGetUniformLocation(program, "rotation"), rotation_sin.x, rotation_sin.y, rotation_sin.z);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &viewMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projectionMatrix[0][0]);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Mesh::SetIndices(std::vector<int> indices)
{

}
void Mesh::SetMaterial(glm::vec3 diffuseColor, glm::vec4 specularColor, float alpha)
{

}
void Mesh::SetMirrorParamters(glm::vec4 prams)
{

}
