#pragma once
#include "Model.h"
#include "../VertexFormat.h"
#include <vector>
#include "../../Rendering/VertexFormat.h"

namespace BasicEngine
{
	namespace Rendering
	{
		namespace Models
		{
			class Mesh : public Model
			{
			public:
				Mesh();
				~Mesh();
				virtual void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)override final;
				virtual void Update() override final;
				template <class T> void Create(std::vector<T>& vertices, int mask);
				void SetIndices(std::vector<int> indices);
				void SetMaterial(glm::vec3 diffuseColor, glm::vec4 specularColor, float alpha);
				void SetMirrorParamters(glm::vec4 prams);

			private:
				glm::vec3 diffuseColor;
				glm::vec4 specularColor;
				float alpha;
				glm::vec4 mirrorParameters; // color + reflect factor
				glm::vec3 rotation, rotation_speed; // TODO 
			};
		}
	}
}