set(sources
    WinMain.cpp)

set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR})

add_fake_library("Application|Windows" ${sources} ${include_dirs})