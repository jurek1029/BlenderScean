#pragma once
#include <iostream>
#include <glew/glew.h>
#include <freeglut/freeglut.h>

namespace BasicEngine
{
	namespace Core
	{
		namespace Init
		{
			class InitGLEW
			{
			public:
				static void Init();
			};
		}
	}
}