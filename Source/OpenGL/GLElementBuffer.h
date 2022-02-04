#pragma once

#include "GLBuffer.h"

/**
 * Element Buffer Object (EBO)
 * Stores indices for rendering from a Vertex Buffer Object (VBO) - See GLVertexBuffer
 */
class GLElementBuffer : public GLBuffer<GL_ELEMENT_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER_BINDING, GLuint>
{
public:
	using GLBuffer::GLBuffer;
};


