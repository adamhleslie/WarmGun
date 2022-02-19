#include "GLVertexArray.h"

GLVertexArray::GLVertexArray()
	: GLBindable<GL_VERTEX_ARRAY_BINDING>(Generate())
{ }

GLVertexArray::~GLVertexArray()
{
	Delete(Get());
}

void GLVertexArray::Bind() const
{
	Bind(Get());
}

void GLVertexArray::ClearBinding()
{
	Bind(0);
}

void GLVertexArray::BindElementBuffer(const GLElementBuffer& elementBuffer) const
{
	glVertexArrayElementBuffer(Get(), elementBuffer.Get());
}

void GLVertexArray::BindVertexBuffer(const GLVertexBuffer& vbo, GLuint bindingIndex, GLintptr offset, GLsizei stride) const
{
	glVertexArrayVertexBuffer(Get(), bindingIndex, vbo.Get(), offset, stride);
}

void GLVertexArray::SetAttribute(GLuint bindingIndex, GLuint attributeIndex, GLint size, GLenum type, GLboolean normalized, GLuint offset) const
{
	glEnableVertexArrayAttrib(Get(), attributeIndex);
	glVertexArrayAttribFormat(Get(), attributeIndex, size, type, normalized, offset);
	glVertexArrayAttribBinding(Get(), attributeIndex, bindingIndex);
}

#pragma region Static
GLuint GLVertexArray::Generate()
{
	GLuint identifier;
	glCreateVertexArrays(1, &identifier);
	return identifier;
}

void GLVertexArray::Bind(GLuint identifier)
{
	glBindVertexArray(identifier);
}

void GLVertexArray::Delete(GLuint identifier)
{
	glDeleteVertexArrays(1, &identifier);
}
#pragma endregion
