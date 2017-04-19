#pragma once
#include <BasicEngine\Engine.h>
#include "CubeIndex.h"
using namespace BasicEngine;
using namespace drawCubeIndex;

int main(int argc, char **argv)
{
	Engine* engine = new Engine();
	engine->Init(3,3);

	//local shaders
	engine->GetShaderManager()->CreateProgram("cubeShader","..\\DrawCube\\Shaders\\VertexShader.shader","..\\DrawCube\\Shaders\\FragmentShader.shader");

	CubeIndex* cube = new CubeIndex();
	cube->SetProgram(engine->GetShaderManager()->GetShader("cubeShader"));
	cube->Create();

	engine->GetModelsManager()->SetModel("cube", cube);

	engine->Run();

	delete engine;
	return 0;
}