#include "Core.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace
{
    constexpr unsigned int g_screenWidth = 800;
    constexpr unsigned int g_screenHeight = 600;
    bool g_renderWireframe = false;

    const char *g_vertexShaderSource = "#version 410 core\n"
                                       "layout (location = 0) in vec3 aPos;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                       "}\0";

    const char *g_fragmentShaderSource = "#version 410 core\n"
                                         "out vec4 FragColor;\n"
                                         "void main()\n"
                                         "{\n"
                                         "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                         "}\0";

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

    GLuint CreateShader(GLenum shaderType, const char* shaderSource)
    {
        GLuint shaderHandle = glCreateShader(shaderType);
        glShaderSource(shaderHandle, 1, &shaderSource, nullptr);
        glCompileShader(shaderHandle);

        GLint success;
        glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(shaderHandle, 512, nullptr, infoLog);
            std::cout << "[Core.CreateShader] Compilation failed: " << infoLog << std::endl;
        }

        return shaderHandle;
    }

    GLuint CreateShaderProgram(std::initializer_list<GLuint> shaderIds)
    {
        if (shaderIds.size() == 0)
        {
            std::cout << "[Core.CreateShaderProgram] No shader IDs provided" << std::endl;
        }

        GLuint shaderProgram = glCreateProgram();
        for (GLuint shaderId : shaderIds)
        {
            glAttachShader(shaderProgram, shaderId);
        }

        glLinkProgram(shaderProgram);

        GLint success;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            std::cout << "[Core.CreateShaderProgram] Compilation failed: " << infoLog << std::endl;
        }

        return shaderProgram;
    }

    void Render_ClearToColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Render_Rectangle_Setup(GLuint& vaoId, GLuint& shaderProgramId)
    {
        // Create shader program
        GLuint vertexShaderId = CreateShader(GL_VERTEX_SHADER, g_vertexShaderSource);
        GLuint fragmentShaderId = CreateShader(GL_FRAGMENT_SHADER, g_fragmentShaderSource);
        shaderProgramId = CreateShaderProgram({ vertexShaderId, fragmentShaderId });

        // Clean up compiled shaders
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);

        // --- //

        // Create a vertex array object (VAO)
        glGenVertexArrays(1, &vaoId);
        glBindVertexArray(vaoId);

        #pragma region VBO
        // Create a vertex buffer object (VBO)
        GLuint vboId;
        glGenBuffers(1, &vboId);
        glBindBuffer(GL_ARRAY_BUFFER, vboId);

        // Define Normalized Device Coordinates (NDC) vertices for rectangle
        GLfloat rectangleVertices[] =
        {
            0.5f,  0.5f, 0.0f,      // top right
            0.5f, -0.5f, 0.0f,      // bottom right
            -0.5f, -0.5f, 0.0f,     // bottom left
            -0.5f,  0.5f, 0.0f      // top left
        };

        // Copy NDCs into the VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), rectangleVertices, GL_STATIC_DRAW);

        // Tell OpenGL how to parse the array of vertices: Pass vertices into the vertex attribute with "(location = 0)"
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        #pragma endregion

        #pragma region EBO
        // Create an element buffer object (EBO)
        GLuint eboId;
        glGenBuffers(1, &eboId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);

        // Define indices for indexed drawing of vertices
        GLuint rectangleIndices[] =
        {
            0, 1, 3,    // first triangle
            1, 2, 3     // second triangle
        };

        // Copy indices into the EBO
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangleIndices), rectangleIndices, GL_STATIC_DRAW);

        // Do NOT unbind the EBO while a VAO is active as the bound EBO is stored in the bound VAO when it is unbound
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        #pragma endregion

        glBindVertexArray(0);
    }

    void Render_Rectangle_Update(GLuint vaoId, GLuint shaderProgramId)
    {
        Render_ClearToColor(0.2f, 0.3f, 0.3f, 1.0f);
        glUseProgram(shaderProgramId);
        glBindVertexArray(vaoId);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
    GLuint vaoId, shaderProgramId;
    Render_Rectangle_Setup(vaoId, shaderProgramId);
    #pragma endregion

    // Render loop until close requested
    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);

        #pragma region Rendering Commands
        Render_Rectangle_Update(vaoId, shaderProgramId);
        #pragma endregion

        // Swap front and back buffers (double buffered)
        glfwSwapBuffers(window);

        // Update glfw events
        glfwPollEvents();
    }

    // Properly clean all of glfw's resources
    glfwTerminate();
}
