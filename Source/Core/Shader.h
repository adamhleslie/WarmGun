#pragma once

#include <filesystem>
#include <string>
#include "GLProgram.h"

class Shader
{
public:
	Shader(const std::string& vertexShader, const std::string& fragmentShader);

    void Use() const;

//    void SetBool(const std::string& name, bool value) const;
//    void SetInt(const std::string& name, bool value) const;
//    void SetFloat(const std::string& name, bool value) const;

private:
	std::shared_ptr<GLProgram> m_shaderProgram;
};
