#pragma once
#include <BasicEngine\Rendering\Models\Model.h>
#include <chrono>

using namespace BasicEngine::Rendering::Models;

using HiResTime = std::chrono::high_resolution_clock;
using MiliSec = std::chrono::milliseconds;
using DeltaTime = std::chrono::duration<float>;

class Multitexturing : public Model
{
	public:
		Multitexturing();
		~Multitexturing();

		void CreateSphere(float radious, unsigned int rings, unsigned int sectors);
	
		virtual void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) override final;
};
