#pragma once

#include <glad/glad.h>

/**
 * Vertex Array Object (VAO)
 * After binding, any subsequent vertex attribute calls will be stored inside
 * Calls: glEnableVertexAttribArray / glDisableVertexAttribArray / glVertexAttribPointer
 */
class GLVertexArray
{
public:
	GLVertexArray();
	virtual ~GLVertexArray();

	GLVertexArray(const GLVertexArray&) = delete;
	GLVertexArray& operator=(const GLVertexArray&) = delete;

	// Explicit conversion function for OpenGL Identifier
	GLuint Get() const { return m_vertexArrayId; }

	void Bind() const;

	static void ClearBinding();
	static GLuint GetBinding();

private:
	GLuint m_vertexArrayId;
};


