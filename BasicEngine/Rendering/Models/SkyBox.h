#pragma once
#include "Mesh.h"
#include "../VertexFormat.h"
#include "../../Rendering/VertexFormat.h"
#include <vector>

namespace BasicEngine
{
	namespace Rendering
	{
		namespace Models
		{
			class SkyBox : public Mesh
			{
			public:
				SkyBox();
				~SkyBox();
				virtual void Draw()override final;
				virtual void Update() override final;

			private:
			};
		}
	}
}