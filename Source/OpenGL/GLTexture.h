#pragma once

#include "GLBindable.h"
#include "glad/glad.h"

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

	void Bind() const override { Bind(0); }
	void Bind(GLenum textureUnit) const;

	static void ClearBinding(GLuint textureUnit = 0);

	void SetWrapping(GLint s, GLint t) const;
	void SetFiltering(GLint minifyingFilter, GLint magnifyingFilter) const;
	void CopyTo(GLubyte* texture, GLsizei width, GLsizei height, GLenum internalFormat, GLenum format) const;
	void GenerateMipmaps() const;

private:
	static GLuint Generate();
	static void Bind(GLuint identifier, GLuint textureUnit);
	static void Delete(GLuint identifier);
};
