#pragma once
#include "ShaderManager.h"
#include "ModelsManager.h"
#include "../Core/Init/IListener.h"

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
			virtual glm::mat4& getViewMatrix();

		private:
			Managers::ModelsManager* modelsManager;
			glm::mat4 viewMatrix;
			glm::mat4 projectionMatrix;
		};
	}
}