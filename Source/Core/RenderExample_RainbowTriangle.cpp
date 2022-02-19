#include "RenderExample_RainbowTriangle.h"

#include "Utilities.h"
#include "Utilities_OpenGL.h"
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
		// Create a vertex array object (VAO)
		std::shared_ptr<GLVertexArray> vertexArray = std::make_shared<GLVertexArray>();

		#pragma region VBO
		// Create a vertex buffer object (VBO)
		std::shared_ptr<GLVertexBuffer> vertexBuffer = std::make_shared<GLVertexBuffer>();

		// Copy normalized device coordinate (NDO) vertices into the VBO
		vertexBuffer->CopyTo(vertices, GL_STATIC_DRAW);

		// Bind VBO to VAO
		vertexArray->BindVertexBuffer(*vertexBuffer, 0, 0, 6 * sizeof(GLfloat));
		vertexArray->SetAttribute(0, 0, 3, GL_FLOAT, false, 0);
		vertexArray->SetAttribute(0, 1, 3, GL_FLOAT, false, (3 * sizeof(GLfloat)));
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

void RenderExample_RainbowTriangle::Render()
{
	Utilities::Render_ClearToColor(0.2f, 0.3f, 0.3f, 1.0f);

	m_shader.Use();

	m_triangle->Bind();
	//m_rectangle->Draw();
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	GLVertexArray::ClearBinding();
}
