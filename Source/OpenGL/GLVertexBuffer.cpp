#include "GLVertexBuffer.h"

void GLVertexBuffer::SetAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, size_t offset) const
{
	// TODO: Check if bound!
	glVertexAttribPointer(index, size, type, normalized, stride, reinterpret_cast<const void*>(offset));
	glEnableVertexAttribArray(index);
}
