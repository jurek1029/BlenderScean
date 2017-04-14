#pragma once
#include <BasicEngine\Engine.h>
#include "Multitexturing.h"
#include "soil\SOIL.h"                          

using namespace BasicEngine;

int main(int argc, char **argv)
{
	Engine* engine = new Engine();
	engine->Init();

	engine->GetShaderManager()->CreateProgram("MultiTexSphereShader","..\\Multitexture\\Shaders\\vertexMulti.shader","..\\Multitexture\\Shaders\\fragMulti.shader");

	Multitexturing* multitexSphere = new Multitexturing();
	int program = engine->GetShaderManager()->GetShader("MultiTexSphereShader");
	if (program != 0)
	{
		multitexSphere->SetProgram(program);
		multitexSphere->CreateSphere(2, 24, 48); //generate sphere geometry and bind ibo, vbo buffers.
	}
	else
	{
		std::cout << "Invalid program."; std::cin.get();
	}
	// Make sure SOIL_FLAG is set to repeat since we will be "scrolling" the UV coordinates
	multitexSphere->SetTexture("BaseTexture", SOIL_load_OGL_texture("..\\Multitexture\\Textures\\nebula1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS));
	multitexSphere->SetTexture("SecondTexture", SOIL_load_OGL_texture("..\\Multitexture\\Textures\\nebula2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS));
	multitexSphere->SetTexture("ThirdTexture", SOIL_load_OGL_texture("..\\Multitexture\\Textures\\nebula3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS));
	multitexSphere->SetTexture("AlphaChanTexture", SOIL_load_OGL_texture("..\\Multitexture\\Textures\\alphaChan.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS));
	multitexSphere->SetTexture("RampTexture", SOIL_load_OGL_texture("..\\Multitexture\\Textures\\ramp.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS));

	engine->GetModelsManager()->SetModel("sphere", multitexSphere);

	engine->Run();

	delete engine;
	return 0;
}