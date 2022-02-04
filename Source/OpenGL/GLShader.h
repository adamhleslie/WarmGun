#pragma once

#include "GLIdentified.h"
#include "glad/glad.h"
#include <string>
#include <memory>

/**
 *	Shader
 */
class GLShader : public GLIdentified
{
public:
	GLShader(GLenum shaderType, const std::string& shaderSource);
	~GLShader() override;

	GLShader(const GLShader&) = delete;
	GLShader& operator=(const GLShader&) = delete;
};
