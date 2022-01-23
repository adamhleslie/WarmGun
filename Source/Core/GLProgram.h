#pragma once

#include "GLShader.h"
#include <glad/glad.h>
#include <initializer_list>
#include <string>

/**
 * Shader Program
 */
class GLProgram
{
public:
	GLProgram(std::initializer_list<std::reference_wrapper<GLShader>> shaderIds);
	virtual ~GLProgram();

	GLProgram(const GLProgram&) = delete;
	GLProgram& operator=(const GLProgram&) = delete;

	// Explicit conversion function for OpenGL Identifier
	GLuint Get() const { return m_programId; }

	void Use() const;

	bool SetUniform(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const;
	bool HasUniform(const std::string& name) const;

private:
	GLint GetUniformLocation(const std::string& name) const;

	GLuint m_programId;
};
