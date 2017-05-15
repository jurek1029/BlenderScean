#pragma once
#include "ShaderManager.h"
#include "ModelsManager.h"
#include "../Core/Init/IListener.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace BasicEngine
{
	namespace Managers
	{
		class SceneManager : public Core::IListener
		{
		public:
			SceneManager();
			~SceneManager();

			virtual void notifyBeginFrame();
			virtual void notifyDisplayFrame();
			virtual void notifyEndFrame();
			virtual void notifyReshape(int width, int height, int previousWidth, int previousHeight);
			virtual void setModelsManager(Managers::ModelsManager*& modelsManager);
			void setShaderManager(Managers::ShaderManager*& shaderManager);
			virtual glm::mat4& getViewMatrix();
			void enableShadows();
			void disableShadows();

			GLuint depthMap;
			glm::mat4 lightSpaceMatrix;
			static glm::mat4 viewMatrix;
			static glm::mat4 projectionMatrix;

		private:
			Managers::ModelsManager* modelsManager;
			Managers::ShaderManager* shaderManager;
			
			bool enabledShadows = true;
			const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
			GLuint depthMapFBO;			
			GLfloat near_plane = 0.3f, far_plane = 30.0f;
			glm::mat4 lightProjection, lightView;
		};
	}
}