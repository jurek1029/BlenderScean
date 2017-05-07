#include "ShaderManager.h"

using namespace BasicEngine;
using namespace Managers;

ShaderManager::ShaderManager() {}

std::map<std::string, GLuint> ShaderManager::programs;

ShaderManager::~ShaderManager()
{
	std::map<std::string, GLuint>::iterator i;
	for (i = programs.begin(); i != programs.end(); ++i)
	{
		GLuint pr = i->second;
		glDeleteProgram(pr);
	}
	programs.clear();
}

std::string ShaderManager::ReadShader(const std::string& filename)
{
	std::string shaderCode;
	std::ifstream file(filename.c_str(), std::ios::in);

	if (!file.good())
	{
		std::cout << "Can't read file " << filename.c_str() << std::endl;
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

GLuint ShaderManager::CreateShader(GLenum shaderType,const std::string& source, const std::string& shaderName)
{
	int compileResult = 0;

	GLint shader = glCreateShader(shaderType);
	const char *shaderCodePtr = source.c_str();
	const int shaderCodeSize = source.size();

	glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

	if (compileResult == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> shaderLog(infoLogLength);
		glGetShaderInfoLog(shader, infoLogLength, nullptr, &shaderLog[0]);
		std::cout << "ERROR compiling shader: " << shaderName.c_str() << std::endl << &shaderLog[0] << std::endl;
		return 0;
	}
	return shader;
}

GLuint ShaderManager::CreateProgram(const std::string& shaderName, const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename)
{
	if (programs.find(shaderName) != programs.end())
	{
		std::cout << "ERROR shader with name: " << shaderName.c_str() << " alredy exist" << std::endl;
		return 0;
	}
	std::string vertexShaderCode = ReadShader(vertexShaderFilename.c_str());
	std::string fragmentShaderCode = ReadShader(fragmentShaderFilename.c_str());

	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderCode, "vertex shader");
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderCode, "fragment shader");

	int linkResult = 0;
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
	if (linkResult == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> programLog(infoLogLength);
		glGetProgramInfoLog(program, infoLogLength, nullptr, &programLog[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl << &programLog[0] << std::endl;
		return 0;
	}

	programs[shaderName] = program;
	return programs[shaderName];
}

GLuint ShaderManager::CreateProgram(const std::string& shaderName, const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename, const std::string& geometryShaderFileName)
{
	if (programs.find(shaderName) != programs.end())
	{
		std::cout << "ERROR shader with name: " << shaderName.c_str() << " alredy exist" << std::endl;
		return 0;
	}
	std::string vertexShaderCode = ReadShader(vertexShaderFilename.c_str());
	std::string fragmentShaderCode = ReadShader(fragmentShaderFilename.c_str());
	std::string geometryShaderCode = ReadShader(geometryShaderFileName.c_str());

	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderCode, "vertex shader");
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderCode, "fragment shader");
	GLuint geometryShader = CreateShader(GL_GEOMETRY_SHADER, geometryShaderCode, "geometry shader");

	int linkResult = 0;
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glAttachShader(program, geometryShader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
	if (linkResult == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> programLog(infoLogLength);
		glGetProgramInfoLog(program, infoLogLength, nullptr, &programLog[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl << &programLog[0] << std::endl;
		return 0;
	}

	programs[shaderName] = program;
	return programs[shaderName];
}

const GLuint ShaderManager::GetShader(const std::string& shaderName)
{
	if (programs.find(shaderName) == programs.end())
	{
		std::cout << "ERROR can't get shader with name: " << shaderName.c_str() << ". Shader don't exist." << std::endl;
		return 0;
	}
	else return programs.at(shaderName);
}

const bool ShaderManager::DeleteShader(const std::string& shaderName)
{
	if (programs.find(shaderName) == programs.end())
	{
		std::cout << "Warning can't delet shader with name: " << shaderName.c_str() <<". Shader don't exist." << std::endl;
		return false;
	}
	else
	{
		GLuint pr = programs.find(shaderName)->second;
		glDeleteProgram(pr);
		programs.erase(shaderName);
		return true;
	}
}