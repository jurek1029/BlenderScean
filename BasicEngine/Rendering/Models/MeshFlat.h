#pragma once
#include "../../PCH.h"

namespace BasicEngine
{
	namespace Rendering
	{
		namespace Models
		{
			class MeshFlat : public Mesh
			{
			public:
				MeshFlat();
				~MeshFlat();
				virtual void Draw()override;
				virtual void DrawDebug() override;
				virtual void Update() override;
				int vertexCount;
			private:
				
			};
		}
	}
}