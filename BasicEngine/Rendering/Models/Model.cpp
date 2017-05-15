#include "Model.h"

using namespace BasicEngine;
using namespace Rendering;
using namespace Models;

Model::Model() {}
Model::~Model()
{
	Destroy();
}

void Model::Draw()
{
}

void Model::Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{
}

void Model::DrawDebug()
{
}

void Model::Update()
{
}

void Model::SetProgram(Shaders::IShader* program){this->program = program;}

void Model::SetProgramDebug(Shaders::IShader* program){	this->programDebug = program;}

GLuint Model::GetVao() const {return vao;}

const std::vector<GLuint>& Model::GetVbos() const {	return vbos; }

const GLuint Model::GetTexture(std::string textureName) const {	return textures.at(textureName); }

void Model::SetTexture(std::string textureName, GLuint texture)
{
	if (texture == 0) return;
	textures[textureName] = texture;
}

void Model::SetTexture(int index, GLuint texture)
{
	if (texture == 0) return;
	auto iter = textures.begin();
	std::advance(iter, index);
	iter->second = texture;
}

void Model::Destroy()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(vbos.size(), vbos.data());
	vbos.clear();
}

std::string Model::GetName() { return name;}