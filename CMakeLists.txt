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

# Add project exe
add_executable(${PROJECT_NAME} WIN32)
setup_cxx_target(${PROJECT_NAME})

# Add internal libraries
add_subdirectory(Source/Core)
add_subdirectory(Source/Application)

# OLD #

## Copy the media directory to the binaries folder
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Media $<TARGET_FILE_DIR:${PROJECT_NAME}>/Media)
#
## On Windows, copy DLLs to bin path.
## If you link more libraries or plugins, make sure to add commands here.
#if(CMAKE_SYSTEM_NAME MATCHES "Windows")
#	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<$<CONFIG:Release>:${OGRE_BINARY_REL}> $<$<NOT:$<CONFIG:Release>>:${OGRE_BINARY_DBG}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
#		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<$<CONFIG:Release>:${OGRE_RenderSystem_GL_REL}> $<$<NOT:$<CONFIG:Release>>:${OGRE_RenderSystem_GL_DBG}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
#		COMMENT "Copying Ogre DLLs to build directory for debugging."
#	)
#endif()
