#include "SkyBox.h"
#include "../../Engine.h"
using namespace BasicEngine::Rendering;
using namespace Models;

SkyBox::SkyBox() {}

SkyBox::~SkyBox() {}

void SkyBox::Update()
{

}

void SkyBox::Draw()
{
	glDepthMask(GL_FALSE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	unsigned int textureLocation = glGetUniformLocation(program->program, "skybox");
	glUniform1i(textureLocation, 0);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indicesLength, GL_UNSIGNED_INT, 0);
	glDepthMask(GL_TRUE);
}

