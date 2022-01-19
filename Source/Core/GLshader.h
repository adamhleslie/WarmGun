#pragma once

#include <glad/glad.h>
#include <string>
#include <memory>

class GLShader
{
public:
	GLShader(GLenum shaderType, const std::string& shaderSource);
	virtual ~GLShader();

	GLShader(const GLShader&) = delete;
	GLShader& operator=(const GLShader&) = delete;

	// Explicit conversion function for OpenGL Identifier
	GLuint Get() const { return m_shaderId; }

private:
	GLuint m_shaderId;
};
