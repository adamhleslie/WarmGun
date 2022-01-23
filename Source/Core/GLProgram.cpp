#include "GLProgram.h"

#include <iostream>

GLProgram::GLProgram(std::initializer_list<std::reference_wrapper<GLShader>> shaders)
{
	if (shaders.size() == 0)
	{
		std::cout << "[GLProgram] No shader IDs provided" << std::endl;
		throw std::invalid_argument("[GLProgram] No shader IDs provided");
	}

	m_programId = glCreateProgram();
	for (const GLShader& shader : shaders)
	{
		glAttachShader(Get(), shader.Get());
	}

	glLinkProgram(Get());

	GLint success;
	glGetProgramiv(Get(), GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(Get(), 512, nullptr, infoLog);
		std::cout << "[GLProgram] Compilation failed: " << infoLog << std::endl;
		throw std::invalid_argument("[GLProgram] Compilation failed");
	}
}

GLProgram::~GLProgram()
{
	glDeleteProgram(m_programId);
}

void GLProgram::Use() const
{
	glUseProgram(Get());
}
