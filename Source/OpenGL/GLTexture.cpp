#include "GLTexture.h"

GLTexture::GLTexture()
	: GLBindable<GL_TEXTURE_BINDING_2D>(Generate())
{ }

GLTexture::~GLTexture()
{
	Delete(Get());
}

void GLTexture::Bind() const
{
	Bind(Get());
}

void GLTexture::BindTo(GLenum textureUnit) const
{
	glActiveTexture(textureUnit);
	Bind();
}

void GLTexture::ClearBinding()
{
	Bind(0);
}

void GLTexture::SetWrapping(GLint s, GLint t)
{
	// TODO: Check if bound!
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t);
}

void GLTexture::SetFiltering(GLint minifyingFilter, GLint magnifyingFilter)
{
	// TODO: Check if bound!
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minifyingFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magnifyingFilter);
}

void GLTexture::CopyTo(GLubyte* texture, GLsizei width, GLsizei height, GLenum format) const
{
	// TODO: Check if bound!
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, texture);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void GLTexture::GenerateMipmaps()
{
	// TODO: Check if bound!
	glGenerateMipmap(GL_TEXTURE_2D);
}

#pragma region Static
GLuint GLTexture::Generate()
{
	GLuint identifier;
	glGenTextures(1, &identifier);
	return identifier;
}

void GLTexture::Bind(GLuint identifier)
{
	glBindTexture(GL_TEXTURE_2D, identifier);
}

void GLTexture::Delete(GLuint identifier)
{
	glDeleteTextures(1, &identifier);
}
#pragma endregion
