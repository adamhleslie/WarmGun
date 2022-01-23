#include "Shader.h"

#include <iostream>
#include <fstream>
#include <system_error>
#include "GLShader.h"

/*
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


//std::string vertexShaderSource;
//if (!ReadFile(vertexShaderPath, vertexShaderSource))
//{
//	throw std::invalid_argument("[Shader] vertexShaderPath could not be read");
//}
//
//std::string fragmentShaderSource;
//if (!ReadFile(fragmentShaderPath, fragmentShaderSource))
//{
//	throw std::invalid_argument("[Shader] fragmentShaderPath could not be read");
//}

}
*/

Shader::Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
	GLShader vertexShader{GL_VERTEX_SHADER, vertexShaderSource};
	GLShader fragmentShader{GL_FRAGMENT_SHADER, fragmentShaderSource};
	m_shaderProgram = std::make_shared<GLProgram>(std::initializer_list<std::reference_wrapper<GLShader>>{vertexShader, fragmentShader});
}

void Shader::Use() const
{
	m_shaderProgram->Use();
}
