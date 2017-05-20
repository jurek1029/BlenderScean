#include "../PCH.h"

using namespace BasicEngine;
using namespace Managers;

glm::mat4 SceneManager::projectionMatrix;
glm::mat4 SceneManager::viewMatrix;

SceneManager::SceneManager()
{
	glEnable(GL_DEPTH_TEST);

	SceneManager::viewMatrix = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 10.0f, 1.0f);

	modelsManager = new ModelsManager();

	if (enabledShadows)
	{
		
		glCullFace(GL_BACK);
		glGenFramebuffers(1, &depthMapFBO);

		glGenTextures(1, &depthMap);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		lightProjection = glm::ortho(-15.0f, 15.0f, -15.0f, 15.0f, near_plane, far_plane);
		lightView = glm::lookAt(glm::vec3(-5.0f, 4.0f, -5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // dla ruchomych œwiate³ trza liczyæ za ka¿dym razem & jak wiecej œwiate³  
		lightSpaceMatrix = lightProjection * lightView;
		shaderManager->CreateProgram("shadowShader", "..\\BasicEngine\\Shaders\\VertexShaderShadow.shader", "..\\BasicEngine\\Shaders\\FragmentShaderShadow.shader");
	}
}

SceneManager::~SceneManager() {	delete modelsManager; }

void SceneManager::notifyBeginFrame() {	modelsManager->Update(); }

void SceneManager::notifyDisplayFrame()
{
	if (enabledShadows)
	{
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);

		modelsManager->temp = shaderManager->GetShader("shadowShader");
		//modelsManager->GetModel("walls").toDraw = false; // Custom
		glUseProgram(modelsManager->temp);
		
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glUniformMatrix4fv(glGetUniformLocation(modelsManager->temp, "lightProjectionMatrix"), 1, false, &lightProjection[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(modelsManager->temp, "lightViewMatrix"), 1, false, &lightView[0][0]);
		modelsManager->Draw(lightProjection, lightView);
		glDisable(GL_CULL_FACE);
		//modelsManager->GetModel("walls").toDraw = true; // Custom
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, Core::Init::InitGLUT::getWindowInfo().width, Core::Init::InitGLUT::getWindowInfo().height);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(51 / 255.0, 51 / 255.0, 51 / 255.0, 1.0);
	modelsManager->temp = 0;
	modelsManager->Draw(SceneManager::projectionMatrix, SceneManager::viewMatrix);
}


void SceneManager::notifyEndFrame()
{

}

void SceneManager::notifyReshape(int width, int height, int previousWidth, int previousHeight)
{
	float ar = (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT);
	float angle = 45.0f, near1 = 0.1f, far1 = 2000.0f;

	SceneManager::projectionMatrix[0][0] = 1.0f / (ar * tan(angle / 2.0f));
	SceneManager::projectionMatrix[1][1] = 1.0f / tan(angle / 2.0f);
	SceneManager::projectionMatrix[2][2] = (-near1 - far1) / (near1 - far1);
	SceneManager::projectionMatrix[2][3] = 1.0f;
	SceneManager::projectionMatrix[3][2] = 2.0f * near1 * far1 / (near1 - far1);
}

void SceneManager::setModelsManager(Managers::ModelsManager*& modelsManager){ this->modelsManager = modelsManager; }
void SceneManager::setShaderManager(Managers::ShaderManager*& shaderManager) { this->shaderManager = shaderManager; }
glm::mat4& SceneManager::getViewMatrix() { return SceneManager::viewMatrix; }
void SceneManager::enableShadows() { enabledShadows = true; }
void SceneManager::disableShadows() { enabledShadows = false; }