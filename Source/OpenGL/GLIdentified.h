#pragma once

#include "glad/glad.h"

class GLIdentified
{
public:
	GLIdentified(GLuint identifier)
		: m_identifier(identifier)
	{ }

	virtual ~GLIdentified() = 0;

	// Explicit conversion function for OpenGL Identifier
	GLuint Get() const { return m_identifier; }
	const GLuint& GetRef() const { return m_identifier; }

private:
	GLuint m_identifier;
};
