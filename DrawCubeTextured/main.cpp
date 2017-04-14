#pragma once
#include <BasicEngine\Engine.h>
#include <BasicEngine\Controls\CameraFPS.h>
#include "CubeTextured.h"
#include "soil\SOIL.h"


using namespace drawCubeTextured;
using namespace BasicEngine;
using namespace Controls;

int main(int argc, char **argv)
{

	Engine* engine = new Engine();
	engine->Init();
	CameraFPS::Init(&engine->GetSceneManager()->getViewMatrix());

	engine->GetShaderManager()->CreateProgram("cubeShader","..\\DrawCubeTextured\\Shaders\\VertexShader.shader","..\\DrawCubeTextured\\Shaders\\FragmentShader.shader");

	CubeTextured* cube = new CubeTextured();
	int program = engine->GetShaderManager()->GetShader("cubeShader");
	if (program != 0)
	{
		cube->SetProgram(program);
		cube->Create();
	}
	else
	{
		std::cout << "invalid program..."; std::cin.get();
	} 
	unsigned int texture = engine->GetTextureLoader()->LoadTexture("..\\DrawCubeTextured\\Crate.bmp", 256, 256);
	//cube->SetTexture("Create", texture);
	cube->SetTexture("Create", SOIL_load_OGL_texture("..\\DrawCubeTextured\\Crate.bmp", SOIL_LOAD_AUTO,	SOIL_CREATE_NEW_ID,	SOIL_FLAG_MIPMAPS));

	engine->GetModelsManager()->SetModel("cube", cube);
	
	engine->Run();

	delete engine;
	return 0;
}