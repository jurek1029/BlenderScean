#pragma once
#include <BasicEngine\Engine.h>
#include <BasicEngine\Controls\CameraFPS.h>
#include <BasicEngine\Rendering\Models\MeshTextured.h>
#include "soil\SOIL.h"
#include <BasicEngine\Shaders\ShaderDefault.h>
#include <BasicEngine\Shaders\ShaderSkyBox.h>
#include <BasicEngine\Shaders\ShaderDebug.h>
#include <BasicEngine\Shaders\ShaderShadow.h>
#include <BasicEngine\Shaders\ShaderMirrorCube.h>

using namespace BasicEngine;
using namespace Controls;



int main(int argc, char **argv)
{

	Engine* engine = new Engine();
	Shaders::ShaderShadow* sh = nullptr;
	Shaders::ShaderSkyBox* shSky = nullptr;
	Shaders::ShaderMirrorCube* shMir = nullptr;
	Shaders::ShaderDebug* shDeb = nullptr;
	engine->Init(3, 3);
	CameraFPS::Init(&engine->GetSceneManager()->getViewMatrix());

	engine->GetShaderManager()->CreateProgram("cubeShader", "..\\Scene\\Shaders\\VertexShader.shader", "..\\Scene\\Shaders\\FragmentShader.shader");
	if (DEBUG)
	{
		engine->GetShaderManager()->CreateProgram("cubeDebugShader", "..\\Scene\\Shaders\\VertShDebug.shader", "..\\Scene\\Shaders\\FragShDebug.shader", "..\\Scene\\Shaders\\GeomShDebug.shader");
	}
	engine->GetShaderManager()->CreateProgram("ShadowProgram", "..\\Scene\\Shaders\\VertShShadow.shader", "..\\Scene\\Shaders\\FragShShadow.shader");
	engine->GetShaderManager()->CreateProgram("cubeMapSky", "..\\Scene\\Shaders\\VertShSkyBox.shader", "..\\Scene\\Shaders\\FragShSkyBox.shader");
	engine->GetShaderManager()->CreateProgram("mirrorMap", "..\\Scene\\Shaders\\VertShMirrorCube.shader", "..\\Scene\\Shaders\\FragShMirrorCube.shader");

	glDepthFunc(GL_LEQUAL);

	vector<const GLchar*> faces;
	faces.push_back("Textures\\awup_rt.tga");
	faces.push_back("Textures\\awup_lf.tga");
	faces.push_back("Textures\\awup_up.tga");
	faces.push_back("Textures\\awup_dn.tga");
	faces.push_back("Textures\\awup_bk.tga");
	faces.push_back("Textures\\awup_ft.tga");
	GLuint cubemapTexture = engine->GetTextureManager()->GetCubemapTexture("cubeMap", faces);

	engine->GetLoaderManager()->loadFile("scean.scn");
	//int program = engine->GetShaderManager()->GetShader("cubeShader"),programDebug = 0;
	int program = engine->GetShaderManager()->GetShader("ShadowProgram"), programDebug = 0,programDef = engine->GetShaderManager()->GetShader("cubeShader");
	int programSky = engine->GetShaderManager()->GetShader("cubeMapSky");
	if (DEBUG) programDebug = engine->GetShaderManager()->GetShader("cubeDebugShader");

	if (program != 0)
	{
		sh = new Shaders::ShaderShadow(program);
		sh->setDepthMap(engine->GetSceneManager()->depthMap);
		sh->setLightSpaceMatrix(engine->GetSceneManager()->lightSpaceMatrix);
		shDeb = new Shaders::ShaderDebug(programDebug);
		shSky = new Shaders::ShaderSkyBox(programSky);
		shMir = new Shaders::ShaderMirrorCube(engine->GetShaderManager()->GetShader("mirrorMap"));
		for (auto m : engine->GetLoaderManager()->meshes)
		{
			if (m->GetName() == "skybox") {

				m->SetProgram(shSky);
				m->texture = cubemapTexture;
			}
			else if (m->GetName() == "mirrorCube") {
				m->toDraw = false;
				m->SetProgram(shMir);
				m->texture = cubemapTexture;
				dynamic_cast<Models::MirrorCube*>(m)->setModelsManager(engine->GetModelsManager());
				dynamic_cast<Models::MirrorCube*>(m)->setCenter(0,5.51f,0);

			}
			else if (m->GetName() == "Sphere") {
				
				m->SetProgram(shMir);
				m->texture = cubemapTexture;
				dynamic_cast<Models::MeshMirror*>(m)->setModelsManager(engine->GetModelsManager());
				dynamic_cast<Models::MeshMirror*>(m)->setCenter(-0.314f, 2.971f, -1.52f);

			}
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