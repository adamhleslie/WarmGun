#include "Shader.h"

#include <iostream>
#include <fstream>
#include <system_error>

namespace
{
    bool ReadFile(const std::filesystem::path& path, std::string& contents)
    {
        // Check for file
        std::error_code filesystemError;
        if (!std::filesystem::is_regular_file(path, filesystemError))
        {
            if (filesystemError)
            {
                std::cout << "[Shader.ReadFile] Error - Path, \"" << path.string() << "\", does not point to a regular file: " << filesystemError.message() << std::endl;
            }

            return false;
        }

        // Open file
        std::ifstream shaderFile{path};
        if (shaderFile.fail())
        {
            std::cout << "[Shader.ReadFile] Error - Opening file, \"" << path.string() << "\", failed" << std::endl;
            return false;
        }

        // Read file into stream
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        if (shaderStream.fail())
        {
            std::cout << "[Shader.ReadFile] Error - Reading file, \"" << path.string() << "\", failed" << std::endl;
            return false;
        }

        contents = shaderStream.str();
        return true;
    }

    bool CreateShader(GLenum shaderType, const std::string& shaderSource, GLuint& shaderId)
    {
        shaderId = glCreateShader(shaderType);
        const char* shaderSourceString = shaderSource.c_str();
        glShaderSource(shaderId, 1, &shaderSourceString, nullptr);
        glCompileShader(shaderId);

        GLint success;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
            std::cout << "[Shader.CreateShader] Compilation failed: " << infoLog << std::endl;
            return false;
        }

        return true;
    }

    bool CreateShaderProgram(std::initializer_list<GLuint> shaderIds, GLuint& shaderProgramId)
    {
        if (shaderIds.size() == 0)
        {
            std::cout << "[Shader.CreateShaderProgram] No shader IDs provided" << std::endl;
            return false;
        }

        shaderProgramId = glCreateProgram();
        for (GLuint shaderId : shaderIds)
        {
            glAttachShader(shaderProgramId, shaderId);
        }

        glLinkProgram(shaderProgramId);

        GLint success;
        glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(shaderProgramId, 512, nullptr, infoLog);
            std::cout << "[Shader.CreateShaderProgram] Compilation failed: " << infoLog << std::endl;
            return false;
        }

        return true;
    }
}

Shader::Shader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragmentShaderPath)
{
    std::string vertexShader;
    if (!ReadFile(vertexShaderPath, vertexShader))
    {
        /// TODO: Handle Error
        return;
    }

    std::string fragmentShader;
    if (!ReadFile(fragmentShaderPath, fragmentShader))
    {
        /// TODO: Handle Error
        return;
    }

    GLuint vertexShaderId;
    if (!CreateShader(GL_VERTEX_SHADER, vertexShader, vertexShaderId))
    {
        /// TODO: Handle Error
        glDeleteShader(vertexShaderId);
        return;
    }

    GLuint fragmentShaderId;
    if (!CreateShader(GL_FRAGMENT_SHADER, fragmentShader, fragmentShaderId))
    {
        /// TODO: Handle Error
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);
        return;
    }

    if (!CreateShaderProgram({ vertexShaderId, fragmentShaderId }, m_shaderProgramId))
    {
        /// TODO: Handle Error
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);
        return;
    }

    // Clean up compiled shaders
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
}
