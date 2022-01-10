#pragma once

#include <glad/glad.h>
#include <filesystem>
#include <string>

class Shader
{
public:
    Shader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragmentShaderPath);

    void Use();

//    void SetBool(const std::string& name, bool value) const;
//    void SetInt(const std::string& name, bool value) const;
//    void SetFloat(const std::string& name, bool value) const;

private:
    GLuint m_shaderProgramId;
};
