#include "MeshMirror.h"
#include "../../Engine.h"
using namespace BasicEngine::Rendering;
using namespace Models;
using namespace BasicEngine::Managers;


MeshMirror::MeshMirror()
{
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glGenTextures(1, &texColorBuffer);
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_CUBE_MAP, texColorBuffer);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	for (int i = 0; i < 6; i++) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, textureFaceWidth, textureFaceHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	}

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X, texColorBuffer, 0);

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, textureFaceWidth, textureFaceHeight);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	tempProjection = glm::perspective(3.1415f / 2.0f, 1.0f, 0.3f, 20.0f);
}

MeshMirror::~MeshMirror() {}

void MeshMirror::setModelsManager(ModelsManager* _modelsManager) { modelsManager = _modelsManager; }
void MeshMirror::setCenter(float x, float y, float z) { xCenter = x; yCenter = y; zCenter = z; }

void MeshMirror::Update()
{
	wasRenderdThisFrame = false;
}

void MeshMirror::Draw()
{
	if (!wasRenderdThisFrame)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glViewport(0, 0, textureFaceWidth, textureFaceHeight);
		toDraw = false;
		for (int i = 0; i < 6; i++)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			switch (i) { // Magia 
			case 0:
				tempView = glm::lookAt(glm::vec3(xCenter, yCenter, zCenter), glm::vec3(xCenter, yCenter, zCenter - 10), glm::vec3(0, -1, 0));
				break;
			case 1:
				tempView = glm::lookAt(glm::vec3(xCenter, yCenter, zCenter), glm::vec3(xCenter + 10, yCenter, zCenter), glm::vec3(0, -1, 0));
				break;
			case 2:
				tempView = glm::lookAt(glm::vec3(xCenter, yCenter, zCenter), glm::vec3(xCenter - 10, yCenter, zCenter), glm::vec3(0, -1, 0));
				break;
			case 3:
				tempView = glm::lookAt(glm::vec3(xCenter, yCenter, zCenter), glm::vec3(xCenter, yCenter + 10, zCenter), glm::vec3(0, 0, -1));
				break;
			case 4:
				tempView = glm::lookAt(glm::vec3(xCenter, yCenter, zCenter), glm::vec3(xCenter, yCenter - 10, zCenter), glm::vec3(0, 0, -1));
				break;
			case 5:
				tempView = glm::lookAt(glm::vec3(xCenter, yCenter, zCenter), glm::vec3(xCenter, yCenter, zCenter + 10), glm::vec3(0, -1, 0));
				break;
			}
			modelsManager->temp = 0;
			modelsManager->Draw(tempProjection, tempView);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, texColorBuffer, 0);
		}
		wasRenderdThisFrame = true;
	}

	modelsManager->temp = 0;
	toDraw = true;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, Core::Init::InitGLUT::getWindowInfo().width, Core::Init::InitGLUT::getWindowInfo().height);

	glUseProgram(program->program);
	program->configureShader(SceneManager::projectionMatrix, SceneManager::viewMatrix);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texColorBuffer);

	unsigned int textureLocation = glGetUniformLocation(program->program, "skybox");
	glUniform1i(textureLocation, 0);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indicesLength, GL_UNSIGNED_INT, 0);
	
	
}
