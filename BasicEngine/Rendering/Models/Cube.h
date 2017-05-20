#pragma once
#include "../../PCH.h"

namespace BasicEngine
{
	namespace Rendering
	{
		namespace Models
		{
			class Cube : public Model
			{
			public:
				Cube();
				~Cube();

				void Create();
				virtual void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)override final;
				virtual void Update() override final;

			private:
				glm::vec3 rotation, rotation_speed;
				time_t timer;
			};
		}
	}
}