#pragma once

#include <filesystem>
#include <string>
#include "GLProgram.h"

/**
 *
 */
class Shader
{
public:
	Shader();
	Shader(const std::string& vertexShader, const std::string& fragmentShader);

    void Use() const;

	bool SetUniform(const std::string& name, float x, float y, float z, float w) const;
	bool SetUniform(const std::string& name, int i) const;

private:
	std::shared_ptr<GLProgram> m_shaderProgram;
};
