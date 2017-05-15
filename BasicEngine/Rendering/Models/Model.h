#pragma once
#include <vector>
#include <map>
#include "../IGameObject.h"
#include "../../Shaders/IShader.h"

namespace BasicEngine
{
	namespace Rendering
	{
		namespace Models
		{
			class Model :public IGameObject
			{
			public:
				Model();
				virtual ~Model();

				virtual void Draw() override;
				virtual void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) override;
				virtual void DrawDebug() override;
				virtual void Update() override;
				virtual void SetProgram(Shaders::IShader* shaderName) override;
				virtual void SetProgramDebug(Shaders::IShader* shaderName);
				virtual void Destroy() override;
				virtual std::string GetName() override;

				virtual GLuint GetVao() const override;
				virtual const std::vector<GLuint>& GetVbos() const override;

				virtual const GLuint GetTexture(std::string textureName) const override;
				virtual void SetTexture(std::string textureName, GLuint texture) override;
				virtual void SetTexture(int index, GLuint texture) override;
				
			protected:
				std::string name;
				GLuint vao;
				std::vector<GLuint> vbos;
				std::map<std::string,GLuint> textures;
			};
		}
	}
}