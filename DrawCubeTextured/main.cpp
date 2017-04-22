#pragma once
#include <BasicEngine\Engine.h>
#include <BasicEngine\Controls\CameraFPS.h>
#include <BasicEngine\Rendering\Models\Mesh.h>
#include "CubeTextured.h"
#include "soil\SOIL.h"


using namespace drawCubeTextured;
using namespace BasicEngine;
using namespace Controls;

int main(int argc, char **argv)
{

	Engine* engine = new Engine();
	engine->Init(3,3);
	CameraFPS::Init(&engine->GetSceneManager()->getViewMatrix());

	engine->GetShaderManager()->CreateProgram("cubeShader","..\\DrawCubeTextured\\Shaders\\VertexShader.shader","..\\DrawCubeTextured\\Shaders\\FragmentShader.shader");

	CubeTextured* cube = new CubeTextured();
	cube->SetTexture("Create", engine->GetTextureManager()->GetTexture("tak.png"));
	engine->GetLoaderManager()->loadFile("scene2.scn");
	int program = engine->GetShaderManager()->GetShader("cubeShader");
	if (program != 0)
	{
		cube->SetProgram(program);
		cube->Create();
		for(auto& m : engine->GetLoaderManager()->meshes)
			m.SetProgram(program);
	}
	else
	{
		std::cout << "invalid program..."; std::cin.get();
	} 
	//unsigned int texture = engine->GetTextureLoader()->LoadTexture("..\\DrawCubeTextured\\Crate.bmp", 256, 256);
	//cube->SetTexture("Create", texture);

	for (auto& m : engine->GetLoaderManager()->meshes)
		engine->GetModelsManager()->SetModel(m.GetName().c_str(), &m);
	engine->GetModelsManager()->SetModel("cube", cube);
	
	printf("size %d\n", engine->GetLoaderManager()->meshes.size());
	
	engine->Run();

	delete engine;
	return 0;
}