#include "RenderExample_Texturing.h"

#include "Utilities.h"
#include "Utilities_OpenGL.h"
#include "GLVertexBuffer.h"
#include "GLElementBuffer.h"
#include <glad/glad.h>
#include <stb_image.h>
#include <filesystem>
#include <array>
#include <iostream>

namespace
{
	#pragma region Shaders
	const std::filesystem::path g_vertexShaderPath{"./Content/Shaders/Textured.vert"};
	const std::filesystem::path g_fragmentShaderPath{"./Content/Shaders/Textured.frag"};
	#pragma endregion

	const std::filesystem::path g_texture1Path{"./Content/Textures/container.jpg"};
	const std::filesystem::path g_texture2Path{"./Content/Textures/awesomeface.png"};

	#pragma region Rectangle
	const std::array<GLfloat, 32> g_rectangleVertices =
	{	// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
	};

	const std::array<GLuint, 6> g_rectangleIndices =
	{
		0, 1, 3,    // top right triangle
		1, 2, 3     // bottom right triangle
	};
	#pragma endregion

	std::shared_ptr<GLVertexArray> CreateVAO(Utilities::CArray<const GLfloat> vertices, Utilities::CArray<const GLuint> indices)
	{
		#pragma region VAO
		// Create a vertex array object (VAO)
		std::shared_ptr<GLVertexArray> vertexArray = std::make_shared<GLVertexArray>();

		#pragma region VBO
		// Create a vertex buffer object (VBO), and bind it
		std::shared_ptr<GLVertexBuffer> vertexBuffer = std::make_shared<GLVertexBuffer>();

		// Copy normalized device coordinate (NDO) vertices into the VBO
		vertexBuffer->CopyTo(vertices, GL_STATIC_DRAW);

		vertexArray->BindVertexBuffer(*vertexBuffer, 0, 0, 8 * sizeof(GLfloat));
		vertexArray->SetAttribute(0, 0, 3, GL_FLOAT, false, 0);
		vertexArray->SetAttribute(0, 1, 3, GL_FLOAT, false, (3 * sizeof(GLfloat)));
		vertexArray->SetAttribute(0, 2, 2, GL_FLOAT, false, (6 * sizeof(GLfloat)));
		#pragma endregion

		#pragma region EBO
		// Create an element buffer object (EBO)
		std::shared_ptr<GLElementBuffer> elementBuffer = std::make_shared<GLElementBuffer>();

		// Copy indices into the EBO
		elementBuffer->CopyTo(indices, GL_STATIC_DRAW);

		// Bind EBO to VAO
		vertexArray->BindElementBuffer(*elementBuffer);
		#pragma endregion
		#pragma endregion

		return vertexArray;
	}

	std::shared_ptr<GLTexture> CreateTexture(const std::filesystem::path& path, GLenum internalFormat, GLenum format, GLint sWrapping, GLint tWrapping, GLint minifyingFilter, GLint magnifyingFilter)
	{
		std::shared_ptr<GLTexture> texture = std::make_shared<GLTexture>();

		// TODO: Wrap stbi usage in resource management class
		int width, height, channelCount;
		unsigned char *data = stbi_load(path.string().c_str(), &width, &height, &channelCount, 0);
		texture->CopyTo(data, width, height, internalFormat, format);
		stbi_image_free(data);

		texture->SetWrapping(sWrapping, tWrapping);
		texture->SetFiltering(minifyingFilter, magnifyingFilter);
		texture->GenerateMipmaps();

		return texture;
	}
}

RenderExample_Texturing::RenderExample_Texturing()
{
	std::string vertexShaderSource;
	Utilities::ReadFile(g_vertexShaderPath, vertexShaderSource);

	std::string fragmentShaderSource;
	Utilities::ReadFile(g_fragmentShaderPath, fragmentShaderSource);

	m_shader = Shader{vertexShaderSource, fragmentShaderSource};
	m_rectangle = CreateVAO(Utilities::ToCArray(g_rectangleVertices), Utilities::ToCArray(g_rectangleIndices));

	stbi_set_flip_vertically_on_load(true);
	m_texture1 = CreateTexture(g_texture1Path, GL_RGB8, GL_RGB, GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	m_shader.SetUniform("texture1", 0);

	m_texture2 = CreateTexture(g_texture2Path, GL_RGBA8, GL_RGBA, GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	m_shader.SetUniform("texture2", 1);
}

void RenderExample_Texturing::Render()
{
	Utilities::Render_ClearToColor(0.2f, 0.3f, 0.3f, 1.0f);

	m_shader.Use();

	m_texture1->Bind(0);
	m_texture2->Bind(1);
	m_rectangle->Bind();
	//m_rectangle->Draw();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	GLTexture::ClearBinding(0);
	GLTexture::ClearBinding(1);
	GLVertexArray::ClearBinding();
}
