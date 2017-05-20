#pragma once
#include "../../PCH.h"

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