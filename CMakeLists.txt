 ##########################################################################
 #                                                                        #
 # This file is part of librnn. Copyright (C) 2003-2006 Keyan Zahedi.     #
 # All rights reserved. Email: keyan@users.sourceforge.net                #
 # Web: http://sourceforge.net/projects/librnn                            #
 #                                                                        #
 # For a list of contributors see the file AUTHORS.                       #
 #                                                                        #
 # librnn is free software; you can redistribute it and/or modify it      #
 # under the terms of the GNU General Public License as published by the  #
 # Free Software Foundation; either version 2 of the License, or (at      #
 # your option) any later version.                                        #
 #                                                                        #
 # librnn is distributed in the hope that it will be useful, but WITHOUT  #
 # ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or  #
 # FITNESS FOR A PARTICULAR PURPOSE.                                      #
 #                                                                        #
 # You should have received a copy of the GNU General Public License      #
 # along with librnn in the file COPYING; if not, write to the Free       #
 # Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA     #
 # 02110-1301, USA.                                                       #
 #                                                                        #
 ##########################################################################



project (librnn)

ENABLE_TESTING()

INCLUDE (CheckIncludeFiles)

set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_BASE_NAME "g++")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DISTRIBUTION "-O3")
set(CMAKE_CXX_COMPILER_FULLPATH "/usr/bin/g++")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR}/lib)

SET(LIBRNN_IMPLEMENTATION_MODE ADJANCENY_VECTOR CACHE STRING
  "Choose the type of implementation, options are: ADJANCENY_LIST ADJANCENY_VECTOR."
  FORCE)

OPTION(LIBRNN_DEBUG
      "Build the librnn using debugging code."
      ON)

OPTION(LIBRNN_USE_LOG4CPP_OUTPUT
      "Building with log4cpp support (test for libs must follow in CMakeLists.txt)"
      OFF)

OPTION(LIBRNN_DOUBLE_PRECISION
      "Build the librnn using double precision."
      ON)


IF(LIBRNN_DEBUG)
  set(CMAKE_BUILD_TYPE Debug)
  message("compiling in librnn in debug mode.")
else(LIBRNN_DEBUG)
  set(CMAKE_BUILD_TYPE Relase)
  message("compiling in librnn in release mode.")
ENDIF(LIBRNN_DEBUG)

IF(LIBRNN_DOUBLE_PRECISION)
  #add_definitions(-DUSE_DOUBLE_PRECISION)
  set(USE_DOUBLE_PRECISION 1)
else(LIBRNN_DOUBLE_PRECISION)
  #add_definitions(-DUSE_FLOAT_PRECISION)
  set(USE_FLOAT_PRECISION 1)
ENDIF(LIBRNN_DOUBLE_PRECISION)

IF(LIBRNN_IMPLEMENTATION_MODE MATCHES ADJANCENY_LIST)
  message("Using adjacency list implementation.")
  #add_definitions(-DIMPL_ADJ_LIST)
  set(IMPL_ADJ_LIST 1)
endif(LIBRNN_IMPLEMENTATION_MODE MATCHES ADJANCENY_LIST)

IF(LIBRNN_IMPLEMENTATION_MODE MATCHES ADJANCENY_VECTOR)
  message("Using adjacency vector implementation.")
  #add_definitions(-DIMPL_ADJ_VECTOR)
  set(IMPL_ADJ_VECTOR 1)
endif(LIBRNN_IMPLEMENTATION_MODE MATCHES ADJANCENY_VECTOR)

IF(LIBRNN_USE_LOG4CPP_OUTPUT)
  message("Using log4cpp support.")
  #add_definitions(-DUSE_LOG4CPP_OUTPUT)
  set(USE_LOG4CPP_OUTPUT 1)
endif(LIBRNN_USE_LOG4CPP_OUTPUT)

IF(LIBRNN_DOUBLE_PRECISION)
  message("Building using double precision.")
else(LIBRNN_DOUBLE_PRECISION)
  message("Building using float precision.")
endif(LIBRNN_DOUBLE_PRECISION)

CONFIGURE_FILE(config.h.cmake "${PROJECT_BINARY_DIR}/include/librnn/config.h")

# Recurse into the "Hello" and "Demo" subdirectories.  This does not actually
# cause another cmake executable to run.  The same process will walk through
# the project's entire directory structure.
add_subdirectory (src)
add_subdirectory (tests)

