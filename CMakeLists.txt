cmake_minimum_required(VERSION 3.13)

# Enable optimized variable evaluation
cmake_policy(SET CMP0053 NEW)

# Enable support for linking libraries across directories
cmake_policy(SET CMP0079 NEW)

# Enable verbose building messages
# set(CMAKE_VERBOSE_MAKEFILE ON)

# Enable verbose find messages
# set(CMAKE_FIND_DEBUG_MODE TRUE)

# PROJECT #
if(NOT DEFINED ENV{PROJECT})
    message(FATAL_ERROR "Please set PROJECT in your environment")
endif()
project("$ENV{PROJECT}" CXX C)

# Log active toolchain
if(DEFINED CMAKE_TOOLCHAIN_FILE)
    message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
endif()

# Set the default search path for modules when using include / find_package
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Log information
message(STATUS "Project Name: " ${PROJECT_NAME})
message(STATUS "Using C compiler: " ${CMAKE_C_COMPILER})
message(STATUS "Using C++ compiler: " ${CMAKE_CXX_COMPILER})

# Add project specific cmake functions
include(project.cxx)
include(project.library)

# Add 3rd party libraries
include(project.opengl)
include(project.glfw)
include(project.glad)
include(project.stb_image)

# Add project exe
add_executable(${PROJECT_NAME} WIN32)
setup_cxx_target(${PROJECT_NAME})

# Add internal libraries
add_subdirectory(Source/OpenGL)
add_subdirectory(Source/Core)
add_subdirectory(Source/Application)

# Make symbolic link for Content folder
set(DATA_SOURCE_DIR "${CMAKE_SOURCE_DIR}/Content")
set(DATA_DESTINATION_DIR "${CMAKE_CURRENT_BINARY_DIR}/Content")
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD COMMAND ${CMAKE_COMMAND}
    -E create_symlink ${DATA_SOURCE_DIR} ${DATA_DESTINATION_DIR}
    DEPENDS ${DATA_DESTINATION_DIR}
    COMMENT "symbolic link ${DATA_SOURCE_DIR} => ${DATA_DESTINATION_DIR}"
)
