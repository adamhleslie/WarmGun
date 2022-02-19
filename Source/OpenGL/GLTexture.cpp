#include "GLTexture.h"

GLTexture::GLTexture()
	: GLBindable<GL_TEXTURE_BINDING_2D>(Generate())
{ }

GLTexture::~GLTexture()
{
	Delete(Get());
}

void GLTexture::Bind(GLuint textureUnit) const
{
	Bind(Get(), textureUnit);
}

void GLTexture::ClearBinding(GLuint textureUnit /* = 0 */)
{
	Bind(0, textureUnit);
}

void GLTexture::SetWrapping(GLint s, GLint t) const
{
	glTextureParameteri(Get(), GL_TEXTURE_WRAP_S, s);
	glTextureParameteri(Get(), GL_TEXTURE_WRAP_T, t);
}

void GLTexture::SetFiltering(GLint minifyingFilter, GLint magnifyingFilter) const
{
	glTextureParameteri(Get(), GL_TEXTURE_MIN_FILTER, minifyingFilter);
	glTextureParameteri(Get(), GL_TEXTURE_MAG_FILTER, magnifyingFilter);
}

void GLTexture::CopyTo(GLubyte* texture, GLsizei width, GLsizei height, GLenum internalFormat, GLenum format) const
{
	glTextureStorage2D(Get(), 1, internalFormat, width, height);
	glTextureSubImage2D(Get(), 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, texture);
}

void GLTexture::GenerateMipmaps() const
{
	glGenerateTextureMipmap(Get());
}

#pragma region Static
GLuint GLTexture::Generate()
{
	GLuint identifier;
	glCreateTextures(GL_TEXTURE_2D, 1, &identifier);
	return identifier;
}

void GLTexture::Bind(GLuint identifier, GLuint textureUnit)
{
	glBindTextureUnit(textureUnit, identifier);
}

void GLTexture::Delete(GLuint identifier)
{
	glDeleteTextures(1, &identifier);
}
#pragma endregion
