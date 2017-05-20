#pragma once
#include "../../PCH.h"

namespace BasicEngine
{
	namespace Rendering
	{
		namespace Models
		{
			class MeshTextured : public Mesh
			{
			public:
				MeshTextured();
				~MeshTextured();
				virtual void Draw()override final;
				virtual void Update() override final;

			private:
			};
		}
	}
}