set(library_name "Application|Windows")

set(sources
    WinMain.cpp)

set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR})

set(dependencies
    Core)

add_fake_library("${library_name}" "${sources}" "${include_dirs}" "${dependencies}")