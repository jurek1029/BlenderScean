#pragma once
#include "../../PCH.h"

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