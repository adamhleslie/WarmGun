cmake_minimum_required(VERSION 2.8)

project("OgreBullet")

option(${PROJECT_NAME}_BUILD_STATIC "Static build")
option(${PROJECT_NAME}_BUILD_DEMOS "Build demos" OFF)
option(${PROJECT_NAME}_USE_BOOST "Use Boost (when Ogre compiled with Boost)" ON)
option(${PROJECT_NAME}_USE_PCH "Use precompiled headers")

if(NOT ${PROJECT_NAME}_BUILD_STATIC)
        set(BUILD_SHARED_LIBS true)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
        add_definitions(-Wall)
        add_definitions(-fPIC) # enable position independant code
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)

find_package(OGRE REQUIRED)
find_package(Bullet REQUIRED)

set(INCLUDE_DIRS
        ${OGRE_INCLUDE_DIR}
        ${BULLET_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/Collisions/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Dynamics/include)

if((${OGRE_VERSION} VERSION_EQUAL "1.9.0") OR (${OGRE_VERSION} VERSION_GREATER "1.9.0"))
	list(APPEND INCLUDE_DIRS ${OGRE_Overlay_INCLUDE_DIR})
#	message("Overlay: ${OGRE_Overlay_INCLUDE_DIR}")
endif()
#message("OGRE_VER: ${OGRE_VERSION}")

if(${PROJECT_NAME}_USE_BOOST)
        find_package(Boost REQUIRED)
        set(INCLUDE_DIRS ${INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
        if(NOT Boost_FOUND)
                message("")
                message("---------------------------------------------")
                message("---- Seems that your system has not Boost.")
                message("---- Set Boost_DIR variable to Boost root dir")
                message("---- if Ogre built with Boost or uncheck ${PROJECT_NAME}_USE_BOOST option.")
                message("---------------------------------------------")
                message("")
        endif()
endif()

include_directories(${INCLUDE_DIRS})

link_directories(${OGRE_LIB_DIR})

set(SOURCES_Col
	Collisions/src/Shapes/OgreBulletCollisionsConeShape.cpp
	Collisions/src/Shapes/OgreBulletCollisionsConvexHullShape.cpp
	Collisions/src/Shapes/OgreBulletCollisionsGImpactShape.cpp
	Collisions/src/Shapes/OgreBulletCollisionsTrimeshShape.cpp
	Collisions/src/Shapes/OgreBulletCollisionsSphereShape.cpp
	Collisions/src/Shapes/OgreBulletCollisionsMinkowskiSumShape.cpp
	Collisions/src/Shapes/OgreBulletCollisionsCylinderShape.cpp
	Collisions/src/Shapes/OgreBulletCollisionsMultiSphereShape.cpp
	Collisions/src/Shapes/OgreBulletCollisionsStaticPlaneShape.cpp
	Collisions/src/Shapes/OgreBulletCollisionsCapsuleShape.cpp
	Collisions/src/Shapes/OgreBulletCollisionsTriangleShape.cpp
	Collisions/src/Shapes/OgreBulletCollisionsCompoundShape.cpp
	Collisions/src/Shapes/OgreBulletCollisionsBoxShape.cpp
	Collisions/src/Shapes/OgreBulletCollisionsTerrainShape.cpp
	Collisions/src/OgreBulletCollisionsObjectState.cpp
	Collisions/src/OgreBulletCollisionsRay.cpp
	Collisions/src/OgreBulletCollisionsWorld.cpp
	Collisions/src/Debug/OgreBulletCollisionsDebugContact.cpp
	Collisions/src/Debug/OgreBulletCollisionsDebugDrawer.cpp
	Collisions/src/Debug/OgreBulletCollisionsDebugShape.cpp
	Collisions/src/Debug/OgreBulletCollisionsDebugLines.cpp
	Collisions/src/OgreBulletCollisionsObject.cpp
	Collisions/src/Utils/OgreBulletCollisionsMeshToShapeConverter.cpp
	Collisions/src/OgreBulletCollisionsShape.cpp)

set(SOURCES_Dyn
	Dynamics/src/OgreBulletDynamicsConstraint.cpp
	Dynamics/src/Constraints/OgreBulletDynamicsRaycastVehicle.cpp
	Dynamics/src/Constraints/OgreBulletDynamicsPoint2pointConstraint.cpp
	Dynamics/src/Constraints/OgreBulletDynamics6DofConstraint.cpp
	Dynamics/src/Constraints/OgreBulletDynamics6DofSpringConstraint.cpp
	Dynamics/src/Constraints/OgreBulletDynamicsConeTwistConstraint.cpp
	Dynamics/src/Constraints/OgreBulletDynamicsHingeConstraint.cpp
	Dynamics/src/OgreBulletDynamicsRigidBody.cpp
	Dynamics/src/OgreBulletDynamicsObjectState.cpp
	Dynamics/src/OgreBulletDynamicsWorld.cpp
	Dynamics/src/Prefab/OgreBulletDynamicsRagDoll.cpp)

if(${PROJECT_NAME}_USE_PCH)
        list(APPEND SOURCES_Col Collisions/src/OgreBulletCollisionsPrecompiled.cpp)
        list(APPEND SOURCES_Dyn Dynamics/src/OgreBulletDynamicsPrecompiled.cpp)
endif()

set(HEADERS_Col_Shapes
	Collisions/include/Shapes/OgreBulletCollisionsMultiSphereShape.h
	Collisions/include/Shapes/OgreBulletCollisionsTriangleShape.h
	Collisions/include/Shapes/OgreBulletCollisionsCompoundShape.h
	Collisions/include/Shapes/OgreBulletCollisionsTerrainShape.h
	Collisions/include/Shapes/OgreBulletCollisionsStaticPlaneShape.h
	Collisions/include/Shapes/OgreBulletCollisionsSphereShape.h
	Collisions/include/Shapes/OgreBulletCollisionsConvexHullShape.h
	Collisions/include/Shapes/OgreBulletCollisionsMinkowskiSumShape.h
	Collisions/include/Shapes/OgreBulletCollisionsCapsuleShape.h
	Collisions/include/Shapes/OgreBulletCollisionsConeShape.h
	Collisions/include/Shapes/OgreBulletCollisionsTrimeshShape.h
	Collisions/include/Shapes/OgreBulletCollisionsBoxShape.h
	Collisions/include/Shapes/OgreBulletCollisionsGImpactShape.h
	Collisions/include/Shapes/OgreBulletCollisionsCylinderShape.h)

set(HEADERS_Col_Debug
	Collisions/include/Debug/OgreBulletCollisionsDebugContact.h
	Collisions/include/Debug/OgreBulletCollisionsDebugDrawer.h
	Collisions/include/Debug/OgreBulletCollisionsDebugLines.h
	Collisions/include/Debug/OgreBulletCollisionsDebugShape.h)

set(HEADERS_Col_Utils
	Collisions/include/Utils/OgreBulletCollisionsMeshToShapeConverter.h
	Collisions/include/Utils/OgreBulletConverter.h)

set(HEADERS_Col
	Collisions/include/OgreBulletCollisionsRay.h
	Collisions/include/OgreBulletCollisions.h
	Collisions/include/OgreBulletCollisionsShape.h
	Collisions/include/OgreBulletCollisionsObjectState.h
	Collisions/include/OgreBulletCollisionsWorld.h
	Collisions/include/OgreBulletCollisionsObject.h
	Collisions/include/OgreBulletCollisionsPreRequisites.h)

set(HEADERS_Dyn_Constraints
	Dynamics/include/Constraints/OgreBulletDynamicsRaycastVehicle.h
	Dynamics/include/Constraints/OgreBulletDynamics6DofSpringConstraint.h
	Dynamics/include/Constraints/OgreBulletDynamicsConeTwistConstraint.h
	Dynamics/include/Constraints/OgreBulletDynamics6DofConstraint.h
	Dynamics/include/Constraints/OgreBulletDynamicsHingeConstraint.h
	Dynamics/include/Constraints/OgreBulletDynamicsPoint2pointConstraint.h)

set(HEADERS_Dyn_Prefab
	Dynamics/include/Prefab/OgreBulletDynamicsRagDoll.h)

set(HEADERS_Dyn
	Dynamics/include/OgreBulletDynamics.h
	Dynamics/include/OgreBulletDynamicsWorld.h
	Dynamics/include/OgreBulletDynamicsRigidBody.h
	Dynamics/include/OgreBulletDynamicsConstraint.h
	Dynamics/include/OgreBulletDynamicsObjectState.h
	Dynamics/include/OgreBulletDynamicsPreRequisites.h)

set(COLLISIONS_LIB "${PROJECT_NAME}Collisions")
set(DYNAMICS_LIB "${PROJECT_NAME}Dynamics")

add_library(${COLLISIONS_LIB} ${SOURCES_Col})
target_link_libraries(${COLLISIONS_LIB} ${BULLET_LIBRARIES} ${OGRE_LIBRARIES})
add_library(${DYNAMICS_LIB} ${SOURCES_Dyn})
target_link_libraries(${DYNAMICS_LIB} ${BULLET_LIBRARIES} ${OGRE_LIBRARIES})

set(INCLUDE_INSTALL_DIR include/${PROJECT_NAME})

set(INCLUDE_INSTALL_COL_DIR ${INCLUDE_INSTALL_DIR}/Collisions)
set(INCLUDE_INSTALL_COL_SHAPES_DIR ${INCLUDE_INSTALL_COL_DIR}/Shapes)
set(INCLUDE_INSTALL_COL_DEBUG_DIR ${INCLUDE_INSTALL_COL_DIR}/Debug)
set(INCLUDE_INSTALL_COL_UTILS_DIR ${INCLUDE_INSTALL_COL_DIR}/Utils)

set(INCLUDE_INSTALL_DYN_DIR ${INCLUDE_INSTALL_DIR}/Dynamics)
set(INCLUDE_INSTALL_DYN_CONSTRAINTS_DIR ${INCLUDE_INSTALL_DYN_DIR}/Constraints)
set(INCLUDE_INSTALL_DYN_PREFAB_DIR ${INCLUDE_INSTALL_DYN_DIR}/Prefab)

install(TARGETS ${COLLISIONS_LIB} ${DYNAMICS_LIB} 
	RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)

if(${PROJECT_NAME}_BUILD_DEMOS)
#	message(STATUS "building demos!")
	add_subdirectory(Demos)
endif(${PROJECT_NAME}_BUILD_DEMOS)

install(FILES ${HEADERS_Col} DESTINATION ${INCLUDE_INSTALL_COL_DIR})
install(FILES ${HEADERS_Col_Shapes} DESTINATION ${INCLUDE_INSTALL_COL_SHAPES_DIR})
install(FILES ${HEADERS_Col_Debug} DESTINATION ${INCLUDE_INSTALL_COL_DEBUG_DIR})
install(FILES ${HEADERS_Col_Utils} DESTINATION ${INCLUDE_INSTALL_COL_UTILS_DIR})

install(FILES ${HEADERS_Dyn} DESTINATION ${INCLUDE_INSTALL_DYN_DIR})
install(FILES ${HEADERS_Dyn_Constraints} DESTINATION ${INCLUDE_INSTALL_DYN_CONSTRAINTS_DIR})
install(FILES ${HEADERS_Dyn_Prefab} DESTINATION ${INCLUDE_INSTALL_DYN_PREFAB_DIR})

install(FILES FindOgreBullet.cmake DESTINATION lib/${PROJECT_NAME}/cmake)

# uninstall target
configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
	IMMEDIATE @ONLY)

add_custom_target(uninstall
	COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

