#pragma once
#include <BasicEngine\Rendering\Models\Model.h>
#include<time.h>
#include<stdarg.h>

using namespace BasicEngine::Rendering::Models;

namespace drawCubeTextured
{
	class CubeTextured : public Model
	{
	public:
		CubeTextured();
		~CubeTextured();

		void Create();
		virtual void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)override final;
		virtual void Update() override final;

	private:
		glm::vec3 rotation, rotation_speed, rotation_sin;
		time_t timer;
	};
}