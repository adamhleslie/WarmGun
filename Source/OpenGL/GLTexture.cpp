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

void GLTexture::ClearBinding()
{
	Bind(0);
}

void GLTexture::CopyTo(GLubyte* texture, GLsizei width, GLsizei height) const
{
	// TODO: Check if bound!
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
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
