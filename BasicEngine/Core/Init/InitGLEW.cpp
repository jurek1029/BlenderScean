#include "InitGLEW.h"

using namespace BasicEngine;
using namespace Core;
using namespace Core::Init;

void InitGLEW::Init()
{
	glewExperimental = true;
	if (glewInit() == GLEW_OK)
		std::cout << "GLEW: Initialize \n";

	if (glewIsSupported("GL_VERSION_4_5"))
		std::cout << "GLEW GL_VERSION_4_5 is 4.5\n ";
	else
		std::cout << "GLEW GL_VERSION_4_5 not suported \n";

}