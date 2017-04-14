#pragma once
#include <BasicEngine\Engine.h>
#include "Cube.h"
using namespace BasicEngine;
int main(int argc, char **argv)
{
	Engine* engine = new Engine();
	engine->Init();

	//local shaders
	engine->GetShaderManager()->CreateProgram("cubeShader","..\\DrawCube\\Shaders\\VertexShader.shader","..\\DrawCube\\Shaders\\FragmentShader.shader");

	Cube* cube = new Cube();
	cube->SetProgram(engine->GetShaderManager()->GetShader("cubeShader"));
	cube->Create();

	engine->GetModelsManager()->SetModel("cube", cube);

	engine->Run();

	delete engine;
	return 0;
}