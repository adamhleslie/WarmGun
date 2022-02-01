#pragma once

#include "GLBindable.h"
#include <glad/glad.h>

/**
 * Vertex Array Object (VAO)
 * After binding, any subsequent vertex attribute calls will be stored inside
 * Calls: glEnableVertexAttribArray / glDisableVertexAttribArray / glVertexAttribPointer
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

private:
	static GLuint Generate();
	static void Bind(GLuint identifier);
	static void Delete(GLuint identifier);
};


