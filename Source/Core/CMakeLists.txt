set(library_name "Core")

set(sources
    Core.h Core.cpp)

set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR})

set(dependencies)

add_static_library("${library_name}" "${sources}" "${include_dirs}" "${dependencies}")
add_library_opengl("${library_name}")
add_library_glfw("${library_name}")
add_library_glad("${library_name}")