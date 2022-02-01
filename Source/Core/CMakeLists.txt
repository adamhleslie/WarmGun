set(library_name "Core")

set(sources
    Utilities.h Utilities.cpp
    Core.h Core.cpp
    Shader.h Shader.cpp
    GLIdentified.h GLIdentified.cpp
    GLBindable.h
    GLShader.h GLShader.cpp
    GLProgram.h GLProgram.cpp
    GLTexture.h GLTexture.cpp
    GLVertexArray.h GLVertexArray.cpp
    GLBuffer.h
    GLVertexBuffer.h GLVertexBuffer.cpp
    GLElementBuffer.h GLElementBuffer.cpp
    RenderExample.h
    RenderExample_RectangleAndTriangle.h RenderExample_RectangleAndTriangle.cpp
    RenderExample_RainbowTriangle.h RenderExample_RainbowTriangle.cpp
    RenderExample_TexturedTriangle.h RenderExample_TexturedTriangle.cpp)

set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR})

set(dependencies)

add_static_library("${library_name}" "${sources}" "${include_dirs}" "${dependencies}")
add_library_opengl("${library_name}")
add_library_glfw("${library_name}")
add_library_glad("${library_name}")
add_library_stb_image("${library_name}")