# .rst:
# FindVmime
# ----------
#
# Try to find the Vmime library (vmime)
#
#
#
# Once done this will define
#
# ::
#
#   VMIME_FOUND - System has vmime
#   VMIME_INCLUDE_DIR - The vmime include directory
#   VMIME_LIBRARIES - The libraries needed to use vmime
#   VMIME_DEFINITIONS - Compiler switches required for using vmime

#=============================================================================
# Copyright 2009 Kitware, Inc.
# Copyright 2009 Philip Lowman <philip@yhbt.com>
# Copyright 2009 Brad Hards <bradh@kde.org>
# Copyright 2006 Alexander Neundorf <neundorf@kde.org>
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)



if (VMIME_INCLUDE_DIR AND VMIME_LIBRARY)
   # in cache already
   set(vmime_FIND_QUIETLY TRUE)
endif ()

if (NOT WIN32)
   # try using pkg-config to get the directories and then use these values
   # in the find_path() and find_library() calls
   # also fills in VMIME_DEFINITIONS, although that isn't normally useful
   find_package(PkgConfig QUIET)
   PKG_CHECK_MODULES(PC_VMIME QUIET vmime)
   set(VMIME_DEFINITIONS ${PC_VMIME_CFLAGS_OTHER})
   set(VMIME_VERSION_STRING ${PC_VMIME_VERSION})
endif ()

find_path(VMIME_INCLUDE_DIR vmime/vmime.hpp
   HINTS
   ${PC_VMIME_INCLUDEDIR}
   ${PC_VMIME_INCLUDE_DIRS}
   ${VMIME_ROOT}/include/
   )

find_library(VMIME_LIBRARY NAMES vmime
   HINTS
   ${PC_VMIME_LIBDIR}
   ${PC_VMIME_LIBRARY_DIRS}
   ${VMIME_ROOT}/lib/
   )

mark_as_advanced(VMIME_INCLUDE_DIR VMIME_LIBRARY)

# handle the QUIETLY and REQUIRED arguments and set Vmime_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Vmime
                                  REQUIRED_VARS VMIME_LIBRARY VMIME_INCLUDE_DIR
                                  VERSION_VAR VMIME_VERSION_STRING)

if(Vmime_FOUND)
    set(VMIME_LIBRARIES    ${VMIME_LIBRARY})
    set(VMIME_INCLUDE_DIRS ${VMIME_INCLUDE_DIR})
endif()