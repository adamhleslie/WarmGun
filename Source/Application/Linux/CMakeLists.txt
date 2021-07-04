set(sources
    main.cpp)

set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR})

add_fake_library("Application|Linux" ${sources} ${include_dirs})