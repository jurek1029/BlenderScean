#pragma once

#include <glew/glew.h>
#include <freeglut/freeglut.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

namespace BasicEngine
{
	namespace Managers
	{

		class ShaderManager
		{
		public:
			ShaderManager();
			~ShaderManager();
			GLuint CreateProgram(const std::string& shaderName, const std::string& VertexShaderFilename, const std::string& FragmentShaderFilename); // shaderName to nazwa programu
			GLuint CreateProgram(const std::string& shaderName, const std::string& VertexShaderFilename, const std::string& FragmentShaderFilename, const std::string& GeometryShaderFilename); // shaderName to nazwa programu
			static const GLuint GetShader(const std::string&);
			static const bool DeleteShader(const std::string&);

		private:
			std::string ReadShader(const std::string& filename);
			GLuint CreateShader(GLenum shaderType, const std::string& source, const std::string& shaderName);

			static std::map<std::string, GLuint> programs;

		};
	}
}
