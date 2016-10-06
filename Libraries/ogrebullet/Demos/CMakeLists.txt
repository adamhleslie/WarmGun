set(DEMOS "demos")

message(STATUS "Building demos!")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

find_package(OIS REQUIRED)
#find_package(Gui3D REQUIRED)

set(LIBS
        ${OGRE_LIBRARIES}
        ${COLLISIONS_LIB}
        ${DYNAMICS_LIB}
        ${BULLET_LIBRARIES}
        ${OIS_LIBRARIES})

if(OSX)
        find_library(COCOA_LIB Cocoa)
        find_library(IOKIT_LIB IOKit)
#        message(STATUS "Cocoa: ${COCOA_LIB}")
        set(LIBS ${LIBS} ${COCOA_LIB} ${IOKIT_LIB})
endif()

message(STATUS "LIBS: ${LIBS}")

set(INCLUDE_DIRS
        ${OGRE_Overlay_INCLUDE_DIR}
        ${OIS_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/common/include)


if(MSVC)
	add_definitions(/W3)
elseif(CMAKE_COMPILER_IS_GNUCXX)
	add_definitions(-Wall)
	add_definitions(-std=c++0x)
endif()

set(SOURCES
#        common/src/OgreBulletSample.cpp
#        common/src/BetaGUI.cpp
        common/src/Gorilla.cpp
#        common/src/OgreBulletGuiListener.cpp
#        common/src/OgreBulletInputListener.cpp
#        common/src/OgreBulletListener.cpp
#        common/src/OgreBulletApplication.cpp
        src/Terrain_Demo.cpp
        src/Vehicle_Demo.cpp
        src/Constraints_Demo.cpp
        src/Primitives_Demo.cpp
        src/Ragdoll_Demo.cpp
        src/main.cpp
        src/TriMesh_Demo.cpp
)

include_directories(${INCLUDE_DIRS})

link_directories(${LIB_DIR})

add_executable(${DEMOS} ${SOURCES})
target_link_libraries(${DEMOS} ${LIBS})
