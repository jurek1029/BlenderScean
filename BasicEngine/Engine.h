#pragma once
#include "PCH.h"

#define DEBUG false

namespace BasicEngine
{
	class Engine
	{

	public:
		Engine();
		~Engine();

		//OpenGL and manager init
		//bool Init();
		bool Init(int majorVersion = 4, int minorVersion = 5);

		//Loop
		void Run();

		//Getters
		Managers::SceneManager*  GetSceneManager()  const;
		Managers::ShaderManager* GetShaderManager() const;
		Managers::ModelsManager* GetModelsManager() const;
		Managers::TextureManager* GetTextureManager() const;
		Managers::LoaderManager* GetLoaderManager() const;

		TextureLoader* GetTextureLoader() const;

	private:
		Managers::SceneManager*  mSceneManager;
		Managers::ShaderManager* mShaderManager;
		Managers::ModelsManager* mModelsManager;
		Managers::LoaderManager* mLoadManager;
		Managers::TextureManager* mTextureManager;
		TextureLoader* mTextureLoader;
	};
}