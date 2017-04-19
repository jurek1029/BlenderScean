#pragma once
#include <string>
#include <vector>

namespace BasicEngine
{
	class Engine;
	namespace Managers
	{
		class LoaderManager
		{
		public:
			LoaderManager(BasicEngine::Engine* _engine);
			LoaderManager(BasicEngine::Engine* _engine, std::vector<std::string> _files);
			~LoaderManager();

			void loadFiles();
			void loadFile(std::string file);
			void setFiles(std::vector<std::string> _files);
			std::vector<std::string> getFiles();
		private:
			std::vector<std::string> files;
			BasicEngine::Engine* engine;
		};
	}
}