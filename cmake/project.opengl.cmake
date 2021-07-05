# Find OpenGL - use add_library_opengl to link
find_package(OpenGL REQUIRED)

function(add_library_opengl target)
    target_include_directories(${target} PRIVATE ${OPENGL_INCLUDE_DIR})
    target_link_libraries(${target} PRIVATE OpenGL::GL)
endfunction()
