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
