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
void Mesh::Create(std::string _name, T* vertices, int lenght)
{
	name = _name;
	GLuint vao;
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, lenght * sizeof(*vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(*vertices), (void*)0);

	if (typeid(*vertices).name() == typeid(VertexFormatN).name())
	{
		//glEnableVertexAttribArray(2);
		//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormatN), (void*)(offsetof(VertexFormatN, VertexFormatN::normal)));
	}
	else if (typeid(*vertices).name() == typeid(VertexFormatUV).name())
	{
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormatUV), (void*)(offsetof(VertexFormatUV, VertexFormatUV::texture)));
	}
	else if (typeid(*vertices).name() == typeid(VertexFormatNUV).name())
	{
		//glEnableVertexAttribArray(2);
		//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormatNUV), (void*)(offsetof(VertexFormatNUV, VertexFormatNUV::normal)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormatNUV), (void*)(offsetof(VertexFormatNUV, VertexFormatNUV::texture)));
	}

	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);

}
template void Mesh::Create<VertexFormatP>(std::string name, VertexFormatP* vertices, int lenght);
template void Mesh::Create<VertexFormatN>(std::string name, VertexFormatN* vertices, int lenght);
template void Mesh::Create<VertexFormatUV>(std::string name, VertexFormatUV* vertices, int lenght);
template void Mesh::Create<VertexFormatNUV>(std::string name, VertexFormatNUV* vertices, int lenght);

void Mesh::Update()
{

}

void Mesh::Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{
	glUseProgram(program);

	//glUniform3f(glGetUniformLocation(program, "rotation"), rotation_sin.x, rotation_sin.y, rotation_sin.z);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &viewMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projectionMatrix[0][0]);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indicesLength, GL_UNSIGNED_INT, 0);
}

void Mesh::SetIndices(unsigned int* indices, int length)
{
	indicesLength = length;
	GLuint ibo;
	glBindVertexArray(vao);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, length * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	this->vbos.push_back(ibo);
}
void Mesh::SetMaterial(glm::vec3 _diffuseColor, glm::vec4 _specularColor, float _alpha)
{
	diffuseColor = _diffuseColor;
	specularColor = _specularColor;
	alpha = _alpha;
}
void Mesh::SetMirrorParamters(glm::vec4 prams)
{
	mirrorParameters = prams;
}

