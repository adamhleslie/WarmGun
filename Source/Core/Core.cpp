#include "Core.h"

#include "Shader.h"
#include "GLVertexArray.h"
#include "GLVertexBuffer.h"
#include "GLElementBuffer.h"
#include "Utilities.h"

#include <iostream>
#include <array>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace
{
	constexpr unsigned int g_screenWidth = 800;
	constexpr unsigned int g_screenHeight = 600;
	bool g_renderWireframe = false;

	#pragma region Shaders
	const std::filesystem::path g_vertexShaderPath{"./Content/Shaders/Simple.vert"};
	const std::filesystem::path g_fragmentShaderPath{"./Content/Shaders/Uniform.frag"};
	#pragma endregion

	#pragma region Rectangle
	const std::array<GLfloat, 12> g_rectangleVertices =
	{
		0.5f, 0.5f, 0.0f,      // top right
		0.5f, -0.5f, 0.0f,      // bottom right
		-0.5f, -0.5f, 0.0f,     // bottom left
		-0.5f, 0.5f, 0.0f      // top left
	};

	const std::array<GLuint, 6> g_rectangleIndices =
	{
		0, 1, 3,    // first triangle
		1, 2, 3     // second triangle
	};
	#pragma endregion

	#pragma region Triangle
	const std::array<GLfloat, 9> g_triangleVertices =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	const std::array<GLuint, 3> g_triangleIndices = { 0, 1, 2 };
	#pragma endregion

    void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void ProcessInput(GLFWwindow* window)
    {
        // Close window w/ "ESC"
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }

        // Toggle between fill and wireframe modes w/ "W"
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            g_renderWireframe = !g_renderWireframe;
            if (g_renderWireframe)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            else
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
        }
    }

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

        // Tell OpenGL how to parse the array of vertices: Pass vertices into the vertex attribute with "(location = 0)"
		vertexBuffer->SetAttribute(0, 3, GL_FLOAT, false, 3 * sizeof(GLfloat));

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

    void Render_ClearToColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

	std::tuple<Shader, std::shared_ptr<GLVertexArray>, std::shared_ptr<GLVertexArray>> Render_RectangleAndTriangle_Setup()
    {
		std::string vertexShaderSource;
		Utilities::ReadFile(g_vertexShaderPath, vertexShaderSource);

	    std::string fragmentShaderSource;
	    Utilities::ReadFile(g_fragmentShaderPath, fragmentShaderSource);

	    // Create shader program
        Shader shader{vertexShaderSource, fragmentShaderSource};

	    std::shared_ptr<GLVertexArray> rectangleVertexArray =
		    CreateVAO(Utilities::ToCArray(g_rectangleVertices), Utilities::ToCArray(g_rectangleIndices));

	    std::shared_ptr<GLVertexArray> triangleVertexArray =
		    CreateVAO(Utilities::ToCArray(g_triangleVertices), Utilities::ToCArray(g_triangleIndices));

		return {shader, rectangleVertexArray, triangleVertexArray};
	}

    void Render_RectangleAndTriangle_Update(const GLVertexArray& rectangle, const GLVertexArray& triangle, const Shader& shader)
    {
        Render_ClearToColor(0.2f, 0.3f, 0.3f, 1.0f);

		shader.Use();
	    shader.SetUniform("uniformColor", 0.0f, (sin(glfwGetTime()) / 2.0f) + 0.5f, 0.0f, 1.0f);

	    rectangle.Bind();
		//rectangle.Draw();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		triangle.Bind();
		//triangle.Draw();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		GLVertexArray::ClearBinding();
    }
}

void Core::Run()
{
    // Set up GLFW with OpenGL 4.6 Core
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Required for Mac OS X
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create initial window
    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW Window", nullptr, nullptr);
    if (!window)
    {
        std::cout << "[Core.Run] Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    // Make initial window our main thread's context
    glfwMakeContextCurrent(window);

    // Initialize GLAD using GLFW to load OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "[Core.Run] Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return;
    }

	// Log OpenGL data
	GLint maxVertexAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttributes);
	std::cout << "[Core.Run] Maximum number of vertex attributes supported: " << maxVertexAttributes << std::endl;

	// Set OpenGL rendering (the viewport) to take up the full window
    glViewport(0, 0, g_screenWidth, g_screenHeight);

    // Set resizing of window to modify the viewport's size
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

    #pragma region Rendering Commands Setup
    auto [ shader, rectangle, triangle ] = Render_RectangleAndTriangle_Setup();
    #pragma endregion

    // Render loop until close requested
    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);

        #pragma region Rendering Commands
        Render_RectangleAndTriangle_Update(*rectangle, *triangle, shader);
        #pragma endregion

        // Swap front and back buffers (double buffered)
        glfwSwapBuffers(window);

        // Update glfw events
        glfwPollEvents();
    }

    // Properly clean all of glfw's resources
    glfwTerminate();
}
