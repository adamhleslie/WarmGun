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

#pragma region Static
GLuint GLVertexArray::Generate()
{
	GLuint identifier;
	glGenVertexArrays(1, &identifier);
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
