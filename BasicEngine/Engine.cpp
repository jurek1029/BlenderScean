#include "Engine.h"
#include <memory>
using namespace BasicEngine;
using namespace Core;


Engine::Engine()
{

}

//You can set params for init
bool Engine::Init(int majorVersion, int minorVersion)
{
	WindowInfo window(std::string("OpenGL Scean"), 400, 200, 800, 600, true);
	ContextInfo context(majorVersion, minorVersion, true);
	FramebufferInfo frameBufferInfo(true, true, true, true);
	Init::InitGLUT::init(window, context, frameBufferInfo);

	mSceneManager = new Managers::SceneManager();
	Init::InitGLUT::setListener(mSceneManager);
	//this was created in  scene manager constructor, now copy here
	mShaderManager = new Managers::ShaderManager();
	mShaderManager->CreateProgram("colorShader", "..\\BasicEngine\\Shaders\\VertexShader.shader", "..\\BasicEngine\\Shaders\\FragmentShader.shader");
	mTextureManager = new Managers::TextureManager();
	mTextureLoader = new TextureLoader();
	mLoadManager = new Managers::LoaderManager(mTextureManager);

	if (mSceneManager && mShaderManager)
	{
		mModelsManager = new Managers::ModelsManager();
		mSceneManager->setModelsManager(mModelsManager);
	}
	else
	{
		return false;
	}

	return true;
}


//Create the loop
void Engine::Run()
{
	Init::InitGLUT::run();
}

Managers::SceneManager* Engine::GetSceneManager() const
{
	return mSceneManager;
}

Managers::ShaderManager* Engine::GetShaderManager() const
{
	return mShaderManager;
}

Managers::ModelsManager* Engine::GetModelsManager() const
{
	return mModelsManager;
}

TextureLoader* Engine::GetTextureLoader() const
{
	return mTextureLoader;
}

Managers::LoaderManager* Engine::GetLoaderManager() const
{
	return mLoadManager;
}

Managers::TextureManager* Engine::GetTextureManager() const
{
	return mTextureManager;
}

Engine::~Engine()
{
	if (mSceneManager)
		delete mSceneManager;

	if (mShaderManager)
		delete mShaderManager;

	if (mModelsManager)
		delete mModelsManager;

	if (mTextureManager)
		delete mTextureManager;

	if (mLoadManager)
		delete mLoadManager;
}