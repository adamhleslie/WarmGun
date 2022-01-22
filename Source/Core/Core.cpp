#include "Core.h"
#include "Shader.h"
#include "GLVertexArray.h"
#include "GLVertexBuffer.h"
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
	const char* g_vertexShaderSource = "#version 410 core\n"
	                                   "layout (location = 0) in vec3 aPos;\n"
	                                   "void main()\n"
	                                   "{\n"
	                                   "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	                                   "}\0";

	const char* g_fragmentShaderSource = "#version 410 core\n"
	                                     "out vec4 FragColor;\n"
	                                     "void main()\n"
	                                     "{\n"
	                                     "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	                                     "}\0";
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

	std::shared_ptr<GLVertexArray> CreateEBO(Utilities::CArray<const GLfloat> vertices, Utilities::CArray<const GLuint> indices, GLuint& eboId)
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

		// TODO: HERE

        // Tell OpenGL how to parse the array of vertices: Pass vertices into the vertex attribute with "(location = 0)"
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(GLfloat), 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        #pragma endregion

        #pragma region EBO
        // Create an element buffer object (EBO)
        glGenBuffers(1, &eboId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);

        // Copy indices into the EBO
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, std::get<1>(indices), std::get<0>(indices), GL_STATIC_DRAW);

        // Do NOT unbind the EBO while a VAO is active as the bound EBO is stored in the bound VAO when it is unbound
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        #pragma endregion

        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
        // Create shader program
        Shader shader{g_vertexShaderSource, g_fragmentShaderSource};

        GLuint rectangleEboId;
	    std::shared_ptr<GLVertexArray> rectangleVertexArray = CreateEBO(Utilities::ToCArray(g_rectangleVertices), Utilities::ToCArray(g_rectangleIndices), rectangleEboId);

        GLuint triangleEboId;
	    std::shared_ptr<GLVertexArray> triangleVertexArray = CreateEBO(Utilities::ToCArray(g_triangleVertices), Utilities::ToCArray(g_triangleIndices), triangleEboId);

		return {shader, rectangleVertexArray, triangleVertexArray};
	}

    void Render_RectangleAndTriangle_Update(GLuint rectangleVaoId, GLuint triangleVaoId, const Shader& shader)
    {
        Render_ClearToColor(0.2f, 0.3f, 0.3f, 1.0f);
		shader.Use();

        glBindVertexArray(rectangleVaoId);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(triangleVaoId);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
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

    // Set OpenGL rendering (the viewport) to take up the full window
    glViewport(0, 0, g_screenWidth, g_screenHeight);

    // Set resizing of window to modify the viewport's size
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

    #pragma region Rendering Commands Setup
    auto [ shader, rectangleVertexArray, triangleVertexArray ] = Render_RectangleAndTriangle_Setup();
    #pragma endregion

    // Render loop until close requested
    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);

        #pragma region Rendering Commands
        Render_RectangleAndTriangle_Update(rectangleVertexArray->Get(), triangleVertexArray->Get(), shader);
        #pragma endregion

        // Swap front and back buffers (double buffered)
        glfwSwapBuffers(window);

        // Update glfw events
        glfwPollEvents();
    }

    // Properly clean all of glfw's resources
    glfwTerminate();
}
