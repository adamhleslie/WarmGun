#include "GLProgram.h"

#include <iostream>

GLProgram::GLProgram(std::initializer_list<std::reference_wrapper<GLShader>> shaders)
	: GLIdentified(glCreateProgram())
{
	if (shaders.size() == 0)
	{
		std::cout << "[GLProgram] No shader IDs provided" << std::endl;
		throw std::invalid_argument("[GLProgram] No shader IDs provided");
	}

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
	glDeleteProgram(Get());
}

void GLProgram::Use() const
{
	glUseProgram(Get());
}

bool GLProgram::SetUniform(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const
{
	GLint uniformLocation = GetUniformLocation(name);
	if (uniformLocation == -1)
	{
		return false;
	}

	glProgramUniform4f(Get(), uniformLocation, v0, v1, v2, v3);

	return true;
}

bool GLProgram::SetUniform(const std::string& name, int i) const
{
	GLint uniformLocation = GetUniformLocation(name);
	if (uniformLocation == -1)
	{
		return false;
	}

	glProgramUniform1i(Get(), uniformLocation, i);

	return true;
}

bool GLProgram::HasUniform(const std::string& name) const
{
	return (GetUniformLocation(name) != -1);
}

GLint GLProgram::GetUniformLocation(const std::string& name) const
{
	return glGetUniformLocation(Get(), name.c_str());
}
