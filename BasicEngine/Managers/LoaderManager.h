#pragma once
#include <string>
#include <vector>
#include "soil\SOIL.h"
#include "..\Rendering\Models\MeshTextured.h"
#include "..\Rendering\Models\MeshFlatTextured.h"
#include "..\Rendering\Models\SkyBox.h"
#include "..\Rendering\Models\MirrorCube.h"
#include "..\Rendering\Models\MeshMirror.h"
#include "TextureManager.h"

namespace BasicEngine
{
	class Engine;
	namespace Managers
	{
		class LoaderManager
		{
		public:
			LoaderManager(TextureManager* textureManager);
			LoaderManager(TextureManager* textureManager,std::vector<std::string> _files);
			~LoaderManager();

			void loadFiles();
			void loadFile(std::string file);
			void setFiles(std::vector<std::string> _files);
			std::vector<std::string> getFiles();
			std::vector<Rendering::Models::Model*> meshes;
		private:
			std::vector<std::string> files;
			Managers::TextureManager* textureManager;
		};
	}
}