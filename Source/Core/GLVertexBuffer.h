#pragma once

#include "Utilities.h"
#include <glad/glad.h>
#include <tuple>

/**
 * Vertex Buffer Object (VBO)
 */
class GLVertexBuffer
{
public:
	GLVertexBuffer();
	virtual ~GLVertexBuffer();

	GLVertexBuffer(const GLVertexBuffer&) = delete;
	GLVertexBuffer& operator=(const GLVertexBuffer&) = delete;

	void Bind() const;

	void CopyTo(const GLfloat* vertices, GLsizeiptr sizeOf, GLenum usage) const;
	void CopyTo(Utilities::CArray<const GLfloat> vertices, GLenum usage) const;

	// Explicit conversion function for OpenGL Identifier
	GLuint Get() const { return m_vertexBufferId; }

private:
	GLuint m_vertexBufferId;
};


