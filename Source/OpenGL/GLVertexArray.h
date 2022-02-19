#pragma once

#include "GLBindable.h"
#include "GLVertexBuffer.h"
#include "GLElementBuffer.h"
#include "glad/glad.h"

/**
 * Vertex Array Object (VAO)
 */
class GLVertexArray : public GLBindable<GL_VERTEX_ARRAY_BINDING>
{
public:
	GLVertexArray();
	~GLVertexArray() override;

	GLVertexArray(const GLVertexArray&) = delete;
	GLVertexArray& operator=(const GLVertexArray&) = delete;

	void Bind() const override;
	static void ClearBinding();

	void BindElementBuffer(const GLElementBuffer& elementBuffer) const;
	void BindVertexBuffer(const GLVertexBuffer& vertexBuffer, GLuint bindingIndex, GLintptr offset, GLsizei stride) const;
	void SetAttribute(GLuint bindingIndex, GLuint attributeIndex, GLint size, GLenum type, GLboolean normalized, GLuint offset) const;

private:
	static GLuint Generate();
	static void Bind(GLuint identifier);
	static void Delete(GLuint identifier);
};


