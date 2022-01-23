#pragma once

#include "GLBuffer.h"

/**
 * Vertex Buffer Object (VBO)
 */
class GLVertexBuffer : public GLBuffer<GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, GLfloat>
{
public:
	using GLBuffer::GLBuffer;

	void SetAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride) const;
};


