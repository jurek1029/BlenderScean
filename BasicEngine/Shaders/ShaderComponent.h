#pragma once
#include "../PCH.h"

namespace BasicEngine {
	namespace Shaders {
		class IShaderComponent {
		public:
			virtual void BindShader();
		private:
			GLuint program;
		};
	}
}
