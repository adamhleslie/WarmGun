# Install script for directory: /u/adamhl/dev/cs354R/ogrebullet

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOgreBulletCollisions.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOgreBulletCollisions.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOgreBulletCollisions.so"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/u/adamhl/dev/cs354R/ogrebullet/Build/libOgreBulletCollisions.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOgreBulletCollisions.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOgreBulletCollisions.so")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOgreBulletCollisions.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOgreBulletCollisions.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOgreBulletDynamics.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOgreBulletDynamics.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOgreBulletDynamics.so"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/u/adamhl/dev/cs354R/ogrebullet/Build/libOgreBulletDynamics.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOgreBulletDynamics.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOgreBulletDynamics.so")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOgreBulletDynamics.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOgreBulletDynamics.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OgreBullet/Collisions" TYPE FILE FILES
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/OgreBulletCollisionsRay.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/OgreBulletCollisions.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/OgreBulletCollisionsShape.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/OgreBulletCollisionsObjectState.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/OgreBulletCollisionsWorld.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/OgreBulletCollisionsObject.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/OgreBulletCollisionsPreRequisites.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OgreBullet/Collisions/Shapes" TYPE FILE FILES
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/Shapes/OgreBulletCollisionsMultiSphereShape.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/Shapes/OgreBulletCollisionsTriangleShape.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/Shapes/OgreBulletCollisionsCompoundShape.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/Shapes/OgreBulletCollisionsTerrainShape.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/Shapes/OgreBulletCollisionsStaticPlaneShape.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/Shapes/OgreBulletCollisionsSphereShape.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/Shapes/OgreBulletCollisionsConvexHullShape.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/Shapes/OgreBulletCollisionsMinkowskiSumShape.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/Shapes/OgreBulletCollisionsCapsuleShape.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/Shapes/OgreBulletCollisionsConeShape.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/Shapes/OgreBulletCollisionsTrimeshShape.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/Shapes/OgreBulletCollisionsBoxShape.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/Shapes/OgreBulletCollisionsGImpactShape.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/Shapes/OgreBulletCollisionsCylinderShape.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OgreBullet/Collisions/Debug" TYPE FILE FILES
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/Debug/OgreBulletCollisionsDebugContact.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/Debug/OgreBulletCollisionsDebugDrawer.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/Debug/OgreBulletCollisionsDebugLines.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/Debug/OgreBulletCollisionsDebugShape.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OgreBullet/Collisions/Utils" TYPE FILE FILES
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/Utils/OgreBulletCollisionsMeshToShapeConverter.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Collisions/include/Utils/OgreBulletConverter.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OgreBullet/Dynamics" TYPE FILE FILES
    "/u/adamhl/dev/cs354R/ogrebullet/Dynamics/include/OgreBulletDynamics.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Dynamics/include/OgreBulletDynamicsWorld.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Dynamics/include/OgreBulletDynamicsRigidBody.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Dynamics/include/OgreBulletDynamicsConstraint.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Dynamics/include/OgreBulletDynamicsObjectState.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Dynamics/include/OgreBulletDynamicsPreRequisites.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OgreBullet/Dynamics/Constraints" TYPE FILE FILES
    "/u/adamhl/dev/cs354R/ogrebullet/Dynamics/include/Constraints/OgreBulletDynamicsRaycastVehicle.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Dynamics/include/Constraints/OgreBulletDynamics6DofSpringConstraint.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Dynamics/include/Constraints/OgreBulletDynamicsConeTwistConstraint.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Dynamics/include/Constraints/OgreBulletDynamics6DofConstraint.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Dynamics/include/Constraints/OgreBulletDynamicsHingeConstraint.h"
    "/u/adamhl/dev/cs354R/ogrebullet/Dynamics/include/Constraints/OgreBulletDynamicsPoint2pointConstraint.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OgreBullet/Dynamics/Prefab" TYPE FILE FILES "/u/adamhl/dev/cs354R/ogrebullet/Dynamics/include/Prefab/OgreBulletDynamicsRagDoll.h")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/OgreBullet/cmake" TYPE FILE FILES "/u/adamhl/dev/cs354R/ogrebullet/FindOgreBullet.cmake")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/u/adamhl/dev/cs354R/ogrebullet/Build/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/u/adamhl/dev/cs354R/ogrebullet/Build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
