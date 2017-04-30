#pragma once
#include <BasicEngine\Engine.h>
#include <BasicEngine\Controls\CameraFPS.h>
#include <BasicEngine\Rendering\Models\MeshTextured.h>
#include "soil\SOIL.h"


using namespace BasicEngine;
using namespace Controls;

int main(int argc, char **argv)
{

	Engine* engine = new Engine();
	engine->Init(3, 3);
	CameraFPS::Init(&engine->GetSceneManager()->getViewMatrix());

	engine->GetShaderManager()->CreateProgram("cubeShader", "..\\DrawCubeTextured\\Shaders\\VertexShader.shader", "..\\DrawCubeTextured\\Shaders\\FragmentShader.shader");

	engine->GetLoaderManager()->loadFile("scean.scn");
	int program = engine->GetShaderManager()->GetShader("cubeShader");
	if (program != 0)
	{
		for (auto m : engine->GetLoaderManager()->meshes)
			m->SetProgram(program);
	}
	else
	{
		std::cout << "invalid program..."; std::cin.get();
	}

	for (auto m : engine->GetLoaderManager()->meshes)
		engine->GetModelsManager()->SetModel(m->GetName().c_str(), m);

	engine->Run();

	delete engine;
	return 0;
}