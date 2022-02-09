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

	void Bind() const override;
	void BindTo(GLenum textureUnit) const;
	static void ClearBinding();

	void SetWrapping(GLint s, GLint t);
	void SetFiltering(GLint minifyingFilter, GLint magnifyingFilter);
	void CopyTo(GLubyte* texture, GLsizei width, GLsizei height, GLenum format) const;
	void GenerateMipmaps();

private:
	static GLuint Generate();
	static void Bind(GLuint identifier);
	static void Delete(GLuint identifier);
};
