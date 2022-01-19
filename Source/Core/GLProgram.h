#pragma once

#include <glad/glad.h>
#include <initializer_list>
#include "GLShader.h"

class GLProgram
{
public:
	GLProgram(std::initializer_list<std::reference_wrapper<GLShader>> shaderIds);
	virtual ~GLProgram();

	GLProgram(const GLProgram&) = delete;
	GLProgram& operator=(const GLProgram&) = delete;

	// Explicit conversion function for OpenGL Identifier
	GLuint Get() const { return m_programId; }

private:
	GLuint m_programId;
};
