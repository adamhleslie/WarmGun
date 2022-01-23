#include "GLVertexArray.h"

GLVertexArray::GLVertexArray()
{
	glGenVertexArrays(1, &m_vertexArrayId);
}

GLVertexArray::~GLVertexArray()
{
	glDeleteVertexArrays(1, &m_vertexArrayId);
}

void GLVertexArray::Bind() const
{
	glBindVertexArray(Get());
}

void GLVertexArray::ClearBinding()
{
	glBindVertexArray(0);
}

GLuint GLVertexArray::GetBinding()
{
	GLint binding;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &binding);
	return binding;
}
