#pragma once
#include <vector>
#include <iostream>
#include <glew/glew.h>
#include <freeglut/freeglut.h>
#include "VertexFormat.h"

namespace BasicEngine
{
	namespace Rendering
	{
		class IGameObject
		{
		public:
			virtual ~IGameObject() = 0;

			virtual void Draw() = 0;
			virtual void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) = 0;
			virtual void Update() = 0;
			virtual void SetProgram(GLuint shaderName) = 0;
			virtual void SetTexture(std::string textureName, GLuint texture) = 0;
			virtual const GLuint GetTexture(std::string textureName) const = 0;
			virtual void Destroy() = 0;
			virtual std::string GetName() = 0;

			virtual GLuint GetVao() const = 0;
			virtual const std::vector<GLuint>& GetVbos() const = 0;
		};
		inline IGameObject::~IGameObject()
		{
		}
	}
}