#include "GLVertexBuffer.h"

void GLVertexBuffer::SetAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride) const
{
	// TODO: Check if bound!
	glVertexAttribPointer(index, size, type, normalized, stride, 0);
	glEnableVertexAttribArray(index);
}
