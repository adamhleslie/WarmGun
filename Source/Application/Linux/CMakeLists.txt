set(library_name "Application|Linux")

set(sources
    main.cpp)

set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR})

set(dependencies
    Core)

add_fake_library("${library_name}" "${sources}" "${include_dirs}" "${dependencies}")