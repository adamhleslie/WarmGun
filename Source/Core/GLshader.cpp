#include "GLShader.h"

#include <iostream>

GLShader::GLShader(GLenum shaderType, const std::string& shaderSource)
{
	m_shaderId = glCreateShader(shaderType);

	const char* shaderSourceString = shaderSource.c_str();
	glShaderSource(Get(), 1, &shaderSourceString, nullptr);
	glCompileShader(Get());

	GLint success;
	glGetShaderiv(Get(), GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(Get(), 512, nullptr, infoLog);
		std::cout << "[Shader.CreateShader] Compilation failed: " << infoLog << std::endl;
		// TODO: Throw exception
	}
}

GLShader::~GLShader()
{
	glDeleteShader(m_shaderId);
}
