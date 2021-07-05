# Adds GLAD target - use add_library_glad to link
add_subdirectory(Libraries/glad)

function(add_library_glad target)
    target_link_libraries(${target} PRIVATE GLAD)
endfunction()