#pragma once
#include "Core\Init\InitGLUT.h"
#include "Managers\SceneManager.h"
#include "Rendering\Texture\TextureLoader.h"
namespace BasicEngine
{
	class Engine
	{

	public:
		Engine();
		~Engine();

		//OpenGL and manager init
		bool Init();

		//Loop
		void Run();

		//Getters
		Managers::SceneManager*  GetSceneManager()  const;
		Managers::ShaderManager* GetShaderManager() const;
		Managers::ModelsManager* GetModelsManager() const;

		TextureLoader* GetTextureLoader() const;

	private:
		Managers::SceneManager*  mSceneManager;
		Managers::ShaderManager* mShaderManager;
		Managers::ModelsManager* mModelsManager;
		TextureLoader* mTextureLoader;
	};
}