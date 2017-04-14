#pragma once
#include "Core\Init\InitGLUT.h"
#include "Managers\SceneManager.h"

using namespace BasicEngine;
using namespace Core;

int main(int argc, char* argv[])
{
	WindowInfo window(std::string("OpenGL Scean"), 400, 200, 800, 600, true);
	ContextInfo context(4, 5, true);
	FramebufferInfo framebufferInfo(true, true, true, true);

	Init::InitGLUT::init(window, context, framebufferInfo);
	IListener* scene = new Managers::SceneManager();
	Init::InitGLUT::setListener(scene);

	Init::InitGLUT::run();

	delete scene;
	return 0;
}