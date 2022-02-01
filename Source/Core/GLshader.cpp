#include "GLShader.h"

#include <iostream>

GLShader::GLShader(GLenum shaderType, const std::string& shaderSource)
	: GLIdentified(glCreateShader(shaderType))
{
	const char* shaderSourceString = shaderSource.c_str();
	glShaderSource(Get(), 1, &shaderSourceString, nullptr);
	glCompileShader(Get());

	GLint success;
	glGetShaderiv(Get(), GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(Get(), 512, nullptr, infoLog);
		std::cout << "[GLShader] Compilation failed: " << infoLog << std::endl;
		throw std::invalid_argument("[GLShader] Compilation failed");
	}
}

GLShader::~GLShader()
{
	glDeleteShader(Get());
}
