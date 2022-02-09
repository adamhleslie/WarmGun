#pragma once

#include "GLIdentified.h"
#include "GLShader.h"
#include "glad/glad.h"
#include <initializer_list>
#include <string>

/**
 * Shader Program
 */
class GLProgram : public GLIdentified
{
public:
	GLProgram(std::initializer_list<std::reference_wrapper<GLShader>> shaderIds);
	~GLProgram() override;

	GLProgram(const GLProgram&) = delete;
	GLProgram& operator=(const GLProgram&) = delete;

	void Use() const;

	bool SetUniform(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const;
	bool SetUniform(const std::string& name, int i) const;
	bool HasUniform(const std::string& name) const;

private:
	GLint GetUniformLocation(const std::string& name) const;
};
