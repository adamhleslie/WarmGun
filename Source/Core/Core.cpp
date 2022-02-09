#include "Core.h"

#include "RenderExample.h"
#include "RenderExample_RectangleAndTriangle.h"
#include "RenderExample_RainbowTriangle.h"
#include "RenderExample_Texturing.h"
#include <iostream>
#include <array>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace
{
	constexpr unsigned int g_screenWidth = 800;
	constexpr unsigned int g_screenHeight = 600;
	bool g_renderWireframe = false;

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
}

void Core::Run()
{
	// TODO: Use macros to create automatic logging w/ [Class.Func] prefix
	//std::cout << "\"" << __FUNCSIG__  << "\" | \"" << __func__ << "\"" << std::endl;
	//std::cout << "\"" << __PRETTY_FUNCTION__  << "\" | \"" << __func__ << "\"" << std::endl;

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

	std::unique_ptr<RenderExample> renderExample = std::unique_ptr<RenderExample>(new RenderExample_Texturing());

    // Render loop until close requested
    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);

	    renderExample->Render();

        // Swap front and back buffers (double buffered)
        glfwSwapBuffers(window);

        // Update glfw events
        glfwPollEvents();
    }

    // Properly clean all of glfw's resources
    glfwTerminate();
}
