#include "RenderExample_RectangleAndTriangle.h"

#include "Utilities.h"
#include "Utilities_OpenGL.h"
#include "GLVertexBuffer.h"
#include "GLElementBuffer.h"
#include <GLFW/glfw3.h>
#include <filesystem>
#include <array>
#include <glad/glad.h>

namespace
{
	#pragma region Shaders
	const std::filesystem::path g_vertexShaderPath{"./Content/Shaders/Simple.vert"};
	const std::filesystem::path g_fragmentShaderPath{"./Content/Shaders/Uniform.frag"};
	#pragma endregion

	#pragma region Rectangle
	const std::array<GLfloat, 12> g_rectangleVertices =
	{
		 0.5f,  0.5f, 0.0f, // top right
		 0.5f, -0.5f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f  // top left
	};

	const std::array<GLuint, 6> g_rectangleIndices =
	{
		0, 1, 3,    // top right triangle
		1, 2, 3     // bottom right triangle
	};
	#pragma endregion

	#pragma region Triangle
	const std::array<GLfloat, 9> g_triangleVertices =
	{   // positions
		-0.5f, -0.5f, 0.0f, // bottom left
		 0.5f, -0.5f, 0.0f, // bottom right
		 0.0f,  0.5f, 0.0f  // top
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

		// Tell OpenGL how to parse the array of vertices: Pass vertices into the vertex attribute with "(location = 0)"
		vertexArray->BindVertexBuffer(*vertexBuffer, 0, 0, 3 * sizeof(GLfloat));
		vertexArray->SetAttribute(0, 0, 3, GL_FLOAT, false, 0);
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

RenderExample_RectangleAndTriangle::RenderExample_RectangleAndTriangle()
{
	std::string vertexShaderSource;
	Utilities::ReadFile(g_vertexShaderPath, vertexShaderSource);

	std::string fragmentShaderSource;
	Utilities::ReadFile(g_fragmentShaderPath, fragmentShaderSource);

	m_shader = Shader{vertexShaderSource, fragmentShaderSource};
	m_rectangle = CreateVAO(Utilities::ToCArray(g_rectangleVertices), Utilities::ToCArray(g_rectangleIndices));
	m_triangle = CreateVAO(Utilities::ToCArray(g_triangleVertices), Utilities::ToCArray(g_triangleIndices));
}

void RenderExample_RectangleAndTriangle::Render()
{
	Utilities::Render_ClearToColor(0.2f, 0.3f, 0.3f, 1.0f);

	m_shader.Use();
	m_shader.SetUniform("uniformColor", 0.0f, (sin(glfwGetTime()) / 2.0f) + 0.5f, 0.0f, 1.0f);

	m_rectangle->Bind();
	//rectangle.Draw();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	m_triangle->Bind();
	//triangle->Draw();
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	GLVertexArray::ClearBinding();
}
