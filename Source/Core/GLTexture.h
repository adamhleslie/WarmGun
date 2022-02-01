#pragma once

#include "GLBindable.h"
#include <glad/glad.h>

/**
 *
 */
class GLTexture : public GLBindable<GL_TEXTURE_BINDING_2D>
{
public:
	GLTexture();
	~GLTexture() override;

	GLTexture(const GLTexture&) = delete;
	GLTexture& operator=(const GLTexture&) = delete;

	void Bind() const override;

	void CopyTo(GLubyte* texture, GLsizei width, GLsizei height) const;

	static void ClearBinding();

private:
	static GLuint Generate();
	static void Bind(GLuint identifier);
	static void Delete(GLuint identifier);
};
