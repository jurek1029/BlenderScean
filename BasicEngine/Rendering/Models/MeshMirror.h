#pragma once
#include "Mesh.h"
#include "../VertexFormat.h"
#include "../../Rendering/VertexFormat.h"
#include "../../Managers/ModelsManager.h"
#include <vector>

namespace BasicEngine
{
	namespace Rendering
	{
		namespace Models
		{
			class MeshMirror : public Mesh
			{
			public:
				MeshMirror();
				~MeshMirror();
				void setModelsManager(Managers::ModelsManager* modelsManager);
				void setCenter(float x, float y, float z);
				virtual void Draw()override final;
				virtual void Update() override final;

			private:
				Managers::ModelsManager* modelsManager;
				GLuint framebuffer;
				GLuint texColorBuffer;
				GLuint rbo;
				glm::mat4 tempProjection, tempView;
				int textureFaceWidth = 256;
				int textureFaceHeight = 256;
				float xCenter = 0, yCenter = 0, zCenter = 0;
			};
		}
	}
}
