#include "Core.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace
{
    void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
}

void Core::Run()
{
    // Set up GLFW with OpenGL 4.6 Core
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create initial window
    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW Window", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    // Make initial window our main thread's context
    glfwMakeContextCurrent(window);

    // Initialize GLAD using GLFW to load OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    // Set OpenGL rendering (the viewport) to take up the full window
    glViewport(0, 0, 800, 600);

    // Set resizing of window to modify the viewport's size
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

    // Render loop until close requested
    while (!glfwWindowShouldClose(window))
    {
        // Swap front and back buffers (double buffered)
        glfwSwapBuffers(window);

        // Update glfw events
        glfwPollEvents();
    }

    // Properly clean all of glfw's resources
    glfwTerminate();
}
