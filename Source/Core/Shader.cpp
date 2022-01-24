#include "Shader.h"

#include <system_error>
#include "GLShader.h"

Shader::Shader()
	: m_shaderProgram(nullptr)
{ }

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

bool Shader::SetUniform(const std::string& name, float x, float y, float z, float w) const
{
	return m_shaderProgram->SetUniform(name, x, y, z, w);
}
