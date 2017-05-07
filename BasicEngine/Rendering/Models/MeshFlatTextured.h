#pragma once
#include "MeshFlat.h"
#include "../VertexFormat.h"
#include "../../Rendering/VertexFormat.h"
#include <vector>

namespace BasicEngine
{
	namespace Rendering
	{
		namespace Models
		{
			class MeshFlatTextured : public MeshFlat
			{
			public:
				MeshFlatTextured();
				~MeshFlatTextured();
				virtual void Draw()override final;
				virtual void Update() override final;

			private:
			};
		}
	}
}