#pragma once
#include "../../PCH.h"

namespace BasicEngine
{
	namespace Rendering
	{
		namespace Models
		{
			class MirrorCube : public MeshFlat
			{
			public:
				MirrorCube();
				~MirrorCube();
				void setModelsManager(Managers::ModelsManager* modelsManager);
				void setCenter(float x, float y, float z);
				virtual void Draw()override final;
				virtual void Update() override final;

			private:
				bool wasRenderdThisFrame = false;
				Managers::ModelsManager* modelsManager;
				GLuint framebuffer;
				GLuint texColorBuffer;
				GLuint rbo;
				glm::mat4 tempProjection, tempView;
				int textureFaceWidth = 256;
				int textureFaceHeight = 256;
				float xCenter=0, yCenter = 0, zCenter = 0;
			};
		}
	}
}
