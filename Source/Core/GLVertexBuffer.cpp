#include "GLVertexBuffer.h"

#include <utility>

GLVertexBuffer::GLVertexBuffer()
{
	glGenBuffers(1, &m_vertexBufferId);
}

GLVertexBuffer::~GLVertexBuffer()
{
	glDeleteBuffers(1, &m_vertexBufferId);
}

void GLVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, Get());
}

void GLVertexBuffer::CopyTo(const GLfloat* vertices, GLsizeiptr sizeOf, GLenum usage) const
{
	// TODO: Check if bound!
	glBufferData(GL_ARRAY_BUFFER, sizeOf, vertices, usage);
}

void GLVertexBuffer::CopyTo(Utilities::CArray<const GLfloat> vertices, GLenum usage) const
{
	CopyTo(std::get<0>(vertices), std::get<1>(vertices), usage);
}
