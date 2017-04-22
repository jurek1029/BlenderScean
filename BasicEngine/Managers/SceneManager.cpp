#include "SceneManager.h"

using namespace BasicEngine;
using namespace Managers;

SceneManager::SceneManager()
{
	glEnable(GL_DEPTH_TEST);

	viewMatrix = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 10.0f, 1.0f);

	modelsManager = new ModelsManager();
}

SceneManager::~SceneManager()
{
	delete modelsManager;
}

void SceneManager::notifyBeginFrame()
{
	modelsManager->Update();
}

void SceneManager::notifyDisplayFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(51 / 255.0, 51 / 255.0, 51 / 255.0, 1.0);

	modelsManager->Draw();
	modelsManager->Draw(projectionMatrix, viewMatrix);
}

void SceneManager::notifyEndFrame()
{

}

void SceneManager::notifyReshape(int width, int height, int previousWidth, int previousHeight)
{
	float ar = (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT);
	float angle = 45.0f, near1 = 0.1f, far1 = 2000.0f;

	projectionMatrix[0][0] = 1.0f / (ar * tan(angle / 2.0f));
	projectionMatrix[1][1] = 1.0f / tan(angle / 2.0f);
	projectionMatrix[2][2] = (-near1 - far1) / (near1 - far1);
	projectionMatrix[2][3] = 1.0f;
	projectionMatrix[3][2] = 2.0f * near1 * far1 / (near1 - far1);
}

void SceneManager::setModelsManager(Managers::ModelsManager*& modelsManager)
{
	this->modelsManager = modelsManager;
}

glm::mat4& SceneManager::getViewMatrix()
{
	return viewMatrix;
}