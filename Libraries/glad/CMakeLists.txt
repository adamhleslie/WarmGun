set(library_name "GLAD")

set(sources
    include/glad/glad.h
    src/glad.c
    include/KHR/khrplatform.h)

set(include_dirs
    include)

set(dependencies)

add_static_library("${library_name}" "${sources}" "${include_dirs}" "${dependencies}")