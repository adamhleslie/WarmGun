set(library_name "STB_IMAGE")

set(sources
    include/stb_image.h
    src/stb_image.cpp)

set(include_dirs
    include)

set(dependencies)

add_static_library("${library_name}" "${sources}" "${include_dirs}" "${dependencies}")