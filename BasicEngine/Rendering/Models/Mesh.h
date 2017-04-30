#pragma once
#include "Model.h"
#include "../VertexFormat.h"
#include "../../Rendering/VertexFormat.h"
#include <vector>

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
				virtual void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)override;
				virtual void Update() override;
				template <class T> void Create(std::string name, T* vertices, int lenght);
				void SetIndices(unsigned int* indices, int length);
				void SetMaterial(glm::vec3 diffuseColor, glm::vec4 specularColor, float alpha);
				void SetMirrorParamters(glm::vec4 prams);

				std::string FragmentShaderName, VertexShaderName;
				std::string ShadersPath;

			protected:
				unsigned int indicesLength;
				glm::vec3 diffuseColor;
				glm::vec4 specularColor;
				float alpha;
				glm::vec4 mirrorParameters; // color + reflect factor
			};
		}
	}
}