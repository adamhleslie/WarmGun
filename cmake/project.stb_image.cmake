# Adds stb_image target - use add_library_stb_image to link
add_subdirectory(Libraries/stb_image)

function(add_library_stb_image target)
    target_link_libraries(${target} PRIVATE STB_IMAGE)
endfunction()