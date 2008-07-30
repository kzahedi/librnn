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

include_directories("${PROJECT_SOURCE_DIR}/include/" "${PROJECT_BINARY_DIR}/include/" "${PROJECT_SOURCE_DIR}/tests/")
link_directories("${PROJECT_BINARY_DIR}/lib/")

REMOVE_DEFINITIONS(-DUSE_VECTOR)
ADD_DEFINITIONS(-DUSE_MATRIX)

IF(LIBRNN_USE_RUNTIME_TEST)
  add_executable(librnnMatrixRuntimeTest ../librnnRuntimeTestMain.cpp ../timing.hpp ../../include/librnn/Logger.hpp)
ENDIF(LIBRNN_USE_RUNTIME_TEST)
add_executable(librnnMatrixUnitTest    ../librnnUnitTestsMain.cpp   ../librnnUnitTests.cpp ../../include/librnn/Logger.hpp)

IF(LIBRNN_USE_RUNTIME_TEST)
  ADD_TEST(matrix-runtime  "${PROJECT_BINARY_DIR}/bin/librnnMatrixRuntimeTest")
ENDIF(LIBRNN_USE_RUNTIME_TEST)
ADD_TEST(matrix-unittest "${PROJECT_BINARY_DIR}/bin/librnnMatrixUnitTest")

IF(LIBRNN_USE_RUNTIME_TEST)
  target_link_libraries(librnnMatrixRuntimeTest rnnMatrix)
ENDIF(LIBRNN_USE_RUNTIME_TEST)
target_link_libraries(librnnMatrixUnitTest    rnnMatrix  cppunit)

IF(LIBRNN_USE_LOG4CPP_OUTPUT)
  IF(LIBRNN_USE_RUNTIME_TEST)
    target_link_libraries(librnnMatrixRuntimeTest log4cpp)
  ENDIF(LIBRNN_USE_RUNTIME_TEST)
  target_link_libraries(librnnMatrixUnitTest    log4cpp)
  message("linking log4cpp to matrix test programs")
ELSE(LIBRNN_USE_LOG4CPP_OUTPUT)
  message("NOT linking log4cpp to matrix test programs")
ENDIF(LIBRNN_USE_LOG4CPP_OUTPUT)

