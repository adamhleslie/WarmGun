#pragma once

#include "GLIdentified.h"

template<GLenum TypeBinding>
class GLBindable : public GLIdentified
{
public:
	GLBindable(GLuint identifier)
		: GLIdentified(identifier)
	{ }

	virtual void Bind() const = 0;

	bool IsBound() const
	{
		return (Get() == GetBinding());
	}

	static GLuint GetBinding()
	{
		GLint binding;
		glGetIntegerv(TypeBinding, &binding);
		return binding;
	}
};
