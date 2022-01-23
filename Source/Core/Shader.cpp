#include "Shader.h"

#include <system_error>
#include "GLShader.h"

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
