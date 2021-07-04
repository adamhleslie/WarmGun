function(add_static_library library_name library_name_visible library_sources library_include_dirs)

    add_library(${library_name} STATIC)
    setup_cxx_target(${library_name})

    target_sources(${library_name} PRIVATE ${library_sources})
    target_include_directories(${library_name} PUBLIC ${library_include_dirs})

    source_group(${library_name_visible} FILES ${library_sources})

    target_link_libraries(${PROJECT_NAME} ${library_name})
    message(STATUS "Added static library " ${library_name_visible})

endfunction()

function(add_fake_library library_name_visible library_sources library_include_dirs)

    target_sources(${PROJECT_NAME} PRIVATE ${library_sources})
    target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_dirs})

    source_group(${library_name_visible} FILES ${library_sources})

    message(STATUS "Added fake library " ${library_name_visible})

endfunction()