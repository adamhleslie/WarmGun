#pragma once

#include "Utilities.h"
#include <glad/glad.h>
#include <tuple>

/**
 * Generic Buffer Object
 */
template<GLenum BufferType, GLenum BufferTypeBinding, class T>
class GLBuffer
{
public:
	GLBuffer()
	{
		glGenBuffers(1, &m_bufferId);
	}

	virtual ~GLBuffer()
	{
		glDeleteBuffers(1, &m_bufferId);
	}

	GLBuffer(const GLBuffer&) = delete;
	GLBuffer& operator=(const GLBuffer&) = delete;

	// Explicit conversion function for OpenGL Identifier
	GLuint Get() const { return m_bufferId; }

	bool IsBound() const
	{
		return (Get() == GetBinding());
	}

	void Bind() const
	{
		glBindBuffer(BufferType, Get());
	}

	void CopyTo(const T* vertices, GLsizeiptr sizeOf, GLenum usage) const
	{
		// TODO: Check if bound!
		glBufferData(BufferType, sizeOf, vertices, usage);
	}

	void CopyTo(Utilities::CArray<const T> vertices, GLenum usage) const
	{
		CopyTo(std::get<0>(vertices), std::get<1>(vertices), usage);
	}

	static void ClearBinding()
	{
		glBindBuffer(BufferType, 0);
	}

	static GLuint GetBinding()
	{
		GLint binding;
		glGetIntegerv(BufferTypeBinding, &binding);
		return binding;
	}

private:
	GLuint m_bufferId;
};


