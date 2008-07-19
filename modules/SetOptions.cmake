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



OPTION(LIBRNN_DEBUG
  "Build the librnn using debugging code."
  ON)

OPTION(LIBRNN_USE_LOG4CPP_OUTPUT
  "Building with log4cpp support (test for libs must follow in CMakeLists.txt)"
  OFF)

OPTION(LIBRNN_DOUBLE_PRECISION
  "Build the librnn using double precision."
  ON)

OPTION(LIBRNN_DOUBLE_PRECISION
  "Build the librnn using double precision."
  ON)

OPTION(LIBRNN_USE_ONLY_FAST_TESTS
  "Build the test only with fast tests."
  OFF)

OPTION(LIBRNN_DESIGN_BY_CONTRACT
  "Build function with design by contract."
  ON)

OPTION(LIBRNN_USE_RUNTIME_TEST
  "Compile and run runtime tests."
  OFF)

SET(LIBRNN_ADDITIONAL_INCLUDE_PATHS "" CACHE STRING
  "Additional include directories.")

SET(LIBRNN_ADDITIONAL_LIBS_PATHS "" CACHE STRING
  "Additional libraries directories.")

IF(LIBRNN_DEBUG)
  set(CMAKE_BUILD_TYPE Debug)
else(LIBRNN_DEBUG)
  set(CMAKE_BUILD_TYPE Relase)
ENDIF(LIBRNN_DEBUG)

include_directories("${LIBRNN_ADDITIONAL_INCLUDE_PATHS}")
link_directories("${LIBRNN_ADDITIONAL_LIBS_PATHS}")

