#pragma once
#include <map>
#include "ShaderManager.h"
#include "../Rendering/IGameObject.h"
#include "../Rendering/Models/Triangle.h"
#include "../Rendering/Models/Quad.h"
#include "../Rendering/Models/Cube.h"
#include "../Rendering/Models/Mesh.h"
#include "../Rendering/Models/MeshTextured.h"
#include "../Rendering/Models/MeshFlat.h"
#include "../Rendering/Models/MeshFlatTextured.h"

using namespace BasicEngine::Rendering;

namespace BasicEngine
{
	namespace Managers
	{
		class ModelsManager
		{
		public:
			ModelsManager();
			~ModelsManager();

			void Draw();
			void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
			void Update();
			void DeleteModel(const std::string& gameModelName);
			IGameObject& GetModel(const std::string& gameModelName) const;
			void SetModel(const std::string& gameObjectName, IGameObject* gameObject);
			GLuint temp = 0;

		private:
			std::map<std::string, IGameObject*> gameModelList; // Potential upgrade to vector
			
		};
	}
}