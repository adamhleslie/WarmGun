#include "RenderExample_RainbowTriangle.h"

#include "Utilities.h"
#include "GLVertexBuffer.h"
#include "GLElementBuffer.h"
#include <filesystem>
#include <array>
#include <glad/glad.h>

namespace
{
	#pragma region Shaders
	const std::filesystem::path g_vertexShaderPath{"./Content/Shaders/VariableLink.vert"};
	const std::filesystem::path g_fragmentShaderPath{"./Content/Shaders/VariableLink.frag"};
	#pragma endregion

	#pragma region Triangle
	const std::array<GLfloat, 18> g_triangleVertices =
	{   // positions        // colors
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // bottom left
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // bottom right
		0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // top
	};

	const std::array<GLuint, 3> g_triangleIndices = { 0, 1, 2 };
	#pragma endregion

	std::shared_ptr<GLVertexArray> CreateVAO(Utilities::CArray<const GLfloat> vertices, Utilities::CArray<const GLuint> indices)
	{
		#pragma region VAO
		// Create a vertex array object (VAO), and bind it
		std::shared_ptr<GLVertexArray> vertexArray = std::make_shared<GLVertexArray>();
		vertexArray->Bind();

		#pragma region VBO
		// Create a vertex buffer object (VBO), and bind it
		std::shared_ptr<GLVertexBuffer> vertexBuffer = std::make_shared<GLVertexBuffer>();
		vertexBuffer->Bind();

		// Copy normalized device coordinate (NDO) vertices into the VBO
		vertexBuffer->CopyTo(vertices, GL_STATIC_DRAW);

		vertexBuffer->SetAttribute(0, 3, GL_FLOAT, false, 6 * sizeof(GLfloat), 0);
		vertexBuffer->SetAttribute(1, 3, GL_FLOAT, false, 6 * sizeof(GLfloat), (3 * sizeof(GLfloat)));

		GLVertexBuffer::ClearBinding();
		#pragma endregion

		#pragma region EBO
		// Create an element buffer object (EBO)
		std::shared_ptr<GLElementBuffer> elementBuffer = std::make_shared<GLElementBuffer>();
		elementBuffer->Bind();

		// Copy indices into the EBO
		elementBuffer->CopyTo(indices, GL_STATIC_DRAW);

		// Do NOT unbind the EBO while a VAO is active as the bound EBO is stored in the bound VAO when it is unbound
		//GLElementBuffer::ClearBinding();
		#pragma endregion

		GLVertexArray::ClearBinding();
		GLElementBuffer::ClearBinding();
		#pragma endregion

		return vertexArray;
	}
}

RenderExample_RainbowTriangle::RenderExample_RainbowTriangle()
{
	std::string vertexShaderSource;
	Utilities::ReadFile(g_vertexShaderPath, vertexShaderSource);

	std::string fragmentShaderSource;
	Utilities::ReadFile(g_fragmentShaderPath, fragmentShaderSource);

	m_shader = Shader{vertexShaderSource, fragmentShaderSource};
	m_triangle = CreateVAO(Utilities::ToCArray(g_triangleVertices), Utilities::ToCArray(g_triangleIndices));
}

void RenderExample_RainbowTriangle::Update()
{
	Utilities::Render_ClearToColor(0.2f, 0.3f, 0.3f, 1.0f);

	m_shader.Use();

	m_triangle->Bind();
	//m_triangle->Draw();
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	GLVertexArray::ClearBinding();
}
