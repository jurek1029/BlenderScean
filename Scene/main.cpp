#pragma once
#include <BasicEngine\Engine.h>
#include <BasicEngine\Controls\CameraFPS.h>
#include <BasicEngine\Rendering\Models\MeshTextured.h>
#include "soil\SOIL.h"
#include <BasicEngine\Shaders\ShaderDefault.h>
#include <BasicEngine\Shaders\ShaderDebug.h>
#include <BasicEngine\Shaders\ShaderShadow.h>

using namespace BasicEngine;
using namespace Controls;



int main(int argc, char **argv)
{

	Engine* engine = new Engine();
	Shaders::ShaderShadow* sh = nullptr;
	Shaders::ShaderDefault* shDef = nullptr;
	Shaders::ShaderDebug* shDeb = nullptr;
	engine->Init(3, 3);
	CameraFPS::Init(&engine->GetSceneManager()->getViewMatrix());

	engine->GetShaderManager()->CreateProgram("cubeShader", "..\\Scene\\Shaders\\VertexShader.shader", "..\\Scene\\Shaders\\FragmentShader.shader");
	if (DEBUG)
	{
		engine->GetShaderManager()->CreateProgram("cubeDebugShader", "..\\Scene\\Shaders\\VertShDebug.shader", "..\\Scene\\Shaders\\FragShDebug.shader", "..\\Scene\\Shaders\\GeomShDebug.shader");
	}
	engine->GetShaderManager()->CreateProgram("ShadowProgram", "..\\Scene\\Shaders\\VertShShadow.shader", "..\\Scene\\Shaders\\FragShShadow.shader");

	engine->GetLoaderManager()->loadFile("scean.scn");
	//int program = engine->GetShaderManager()->GetShader("cubeShader"),programDebug = 0;
	int program = engine->GetShaderManager()->GetShader("ShadowProgram"), programDebug = 0,programDef = engine->GetShaderManager()->GetShader("cubeShader");
	if (DEBUG) programDebug = engine->GetShaderManager()->GetShader("cubeDebugShader");

	if (program != 0)
	{
		sh = new Shaders::ShaderShadow(program);
		sh->setDepthMap(engine->GetSceneManager()->depthMap);
		sh->setLightSpaceMatrix(engine->GetSceneManager()->lightSpaceMatrix);
		shDeb = new Shaders::ShaderDebug(programDebug);
		shDef = new Shaders::ShaderDefault(programDef);
		for (auto m : engine->GetLoaderManager()->meshes)
		{
			if (m->GetName() == "skybox") m->SetProgram(shDef);
			else m->SetProgram(sh);
			if(DEBUG) m->SetProgramDebug(shDeb);
		}
	}
	else
	{
		std::cout << "invalid program..."; std::cin.get();
	}

	for (auto m : engine->GetLoaderManager()->meshes)
		engine->GetModelsManager()->SetModel(m->GetName().c_str(), m);

	engine->Run();
	delete sh;
	delete shDeb;
	delete engine;
	return 0;
}