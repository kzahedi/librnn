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

ADD_DEFINITIONS(-DUSE_VECTOR)

IF(LIBRNN_USE_RUNTIME_TEST)
  add_executable(librnnRuntimeTest ../librnnRuntimeTestMain.cpp ../timing.hpp ../../include/librnn/Logger.hpp)
ENDIF(LIBRNN_USE_RUNTIME_TEST)
add_executable(librnnUnitTest    ../librnnUnitTestsMain.cpp   ../librnnUnitTests.cpp ../../include/librnn/Logger.hpp)

IF(LIBRNN_USE_RUNTIME_TEST)
  ADD_TEST(vector-runtime  "${PROJECT_BINARY_DIR}/bin/librnnRuntimeTest")
ENDIF(LIBRNN_USE_RUNTIME_TEST)
ADD_TEST(vector-unittest "${PROJECT_BINARY_DIR}/bin/librnnUnitTest")

IF(LIBRNN_USE_RUNTIME_TEST)
  target_link_libraries(librnnRuntimeTest rnnVector)
ENDIF(LIBRNN_USE_RUNTIME_TEST)
target_link_libraries(librnnUnitTest    rnnVector rnnMatrix cppunit)

IF(LIBRNN_USE_LOG4CPP_OUTPUT)
  IF(LIBRNN_USE_RUNTIME_TEST)
    target_link_libraries(librnnRuntimeTest log4cpp)
  ENDIF(LIBRNN_USE_RUNTIME_TEST)
  target_link_libraries(librnnUnitTest    log4cpp)
  message("linking log4cpp to vector test programs")
ELSE(LIBRNN_USE_LOG4CPP_OUTPUT)
  message("NOT linking log4cpp to vector test programs")
ENDIF(LIBRNN_USE_LOG4CPP_OUTPUT)

