# Application Interface setup
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_subdirectory(Windows)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_subdirectory(Linux)
else() # Unknown
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()
