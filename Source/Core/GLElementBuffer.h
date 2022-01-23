#pragma once

#include "GLBuffer.h"

/**
 * Element Buffer Object (EBO)
 */
class GLElementBuffer : public GLBuffer<GL_ELEMENT_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER_BINDING, GLuint>
{
public:
	using GLBuffer::GLBuffer;
};


