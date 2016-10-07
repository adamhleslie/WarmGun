# - Find Gui3D
# Find the native Gui3D includes and library
#
#   Gui3D_FOUND       - True if Gui3D found.
#   Gui3D_INCLUDE_DIR - where to find includes
#   Gui3D_LIBRARIES   - List of libraries when using Gui3D.
#

if(Gui3D_INCLUDE_DIR)
    # Already in cache, be silent
    set(Gui3D_FIND_QUIETLY TRUE)
endif(Gui3D_INCLUDE_DIR)

find_path(Gui3D_INCLUDE_DIR "Gui3D.h"
          PATH_SUFFIXES "Gui3D" )

find_library(Gui3D_LIB "Gui3D")

SET(Gui3D_LIBRARIES OgreBulletDyn OgreBulletCol)

# handle the QUIETLY and REQUIRED arguments and set OGREBULLET_FOUND to TRUE if
# all listed variables are TRUE
include("FindPackageHandleStandardArgs")
FIND_PACKAGE_HANDLE_STANDARD_ARGS("Gui3D" DEFAULT_MSG Gui3D_INCLUDE_DIR Gui3D_LIBRARIES)

mark_as_advanced(Gui3D_INCLUDE_DIR Gui3D_LIBRARIES)

