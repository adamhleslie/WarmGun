#pragma once

#include "Utilities_OpenGL.h"
#include "GLBindable.h"
#include "glad/glad.h"
#include <tuple>

/**
 * Generic Buffer Object
 */
template<GLenum BufferType, GLenum BufferTypeBinding, class T>
class GLBuffer : public GLBindable<BufferTypeBinding>
{
public:
	GLBuffer()
		: GLBindable<BufferTypeBinding>(Generate())
	{ }

	virtual ~GLBuffer()
	{
		Delete(GLIdentified::Get());
	}

	GLBuffer(const GLBuffer&) = delete;
	GLBuffer& operator=(const GLBuffer&) = delete;

	void Bind() const override
	{
		Bind(GLIdentified::Get());
	}

	static void ClearBinding()
	{
		Bind(0);
	}

	void CopyTo(const T* vertices, GLsizeiptr sizeOf, GLenum usage) const
	{
		glNamedBufferData(GLIdentified::Get(), sizeOf, vertices, usage);
	}

	void CopyTo(Utilities::CArray<const T> vertices, GLenum usage) const
	{
		CopyTo(std::get<0>(vertices), std::get<1>(vertices), usage);
	}

private:
	static GLuint Generate()
	{
		GLuint identifier;
		glCreateBuffers(1, &identifier);
		return identifier;
	}

	static void Bind(GLuint identifier)
	{
		glBindBuffer(BufferType, identifier);
	}

	static void Delete(GLuint identifier)
	{
		glDeleteBuffers(1, &identifier);
	}
};


