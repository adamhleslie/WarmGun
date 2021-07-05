function(add_static_library library_name library_sources library_include_dirs library_dependencies)

    add_library(${library_name} STATIC)
    setup_cxx_target(${library_name})

    if (library_sources)
        target_sources(${library_name} PRIVATE ${library_sources})
        source_group(${library_name} FILES ${library_sources})
    endif()

    if (library_include_dirs)
        target_include_directories(${library_name} PUBLIC ${library_include_dirs})
    endif()

    if (library_dependencies)
        target_link_libraries(${library_name} PRIVATE ${library_dependencies})
    endif()

    message(STATUS "Added static library " ${library_name})

endfunction()

function(add_fake_library library_name library_sources library_include_dirs library_dependencies)

    if (library_sources)
        target_sources(${PROJECT_NAME} PRIVATE ${library_sources})
        source_group(${library_name} FILES ${library_sources})
    endif()

    if (library_include_dirs)
        target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_dirs})
    endif()

    if (library_dependencies)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${library_dependencies})
    endif()

    message(STATUS "Added fake library " ${library_name})

endfunction()