set(library_name "OpenGL")

set(sources
    Utilities_OpenGL.h Utilities_OpenGL.cpp
    GLIdentified.h GLIdentified.cpp
    GLBindable.h
    GLShader.h GLShader.cpp
    GLProgram.h GLProgram.cpp
    GLTexture.h GLTexture.cpp
    GLVertexArray.h GLVertexArray.cpp
    GLBuffer.h
    GLVertexBuffer.h GLVertexBuffer.cpp
    GLElementBuffer.h GLElementBuffer.cpp)

set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR})

set(dependencies)

add_static_library("${library_name}" "${sources}" "${include_dirs}" "${dependencies}")
add_library_opengl("${library_name}")
add_library_glad("${library_name}")