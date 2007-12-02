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
 # FITNESS __FOR A PARTICULAR PURPOSE.                                      #
 #                                                                        #
 # You should have received a copy of the GNU General Public License      #
 # along with librnn in the file COPYING; if not, write to the Free       #
 # Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA     #
 # 02110-1301, USA.                                                       #
 #                                                                        #
 ##########################################################################

add_executable(librnnRuntimeTest librnnRuntimeTestMain.cpp timing.hpp)
add_executable(librnnUnitTest    librnnUnitTestsMain.cpp   librnnUnitTests.cpp)

ADD_TEST(runtime  "${PROJECT_BINARY_DIR}/bin/librnnRuntimeTest")
ADD_TEST(unittest "${PROJECT_BINARY_DIR}/bin/librnnUnitTest")

include_directories("${PROJECT_SOURCE_DIR}/include/" "${PROJECT_BINARY_DIR}/include/" "${PROJECT_SOURCE_DIR}/tests/")
link_directories("${PROJECT_BINARY_DIR}/lib/")

target_link_libraries(librnnUnitTest    rnn  cppunit)
target_link_libraries(librnnRuntimeTest rnn)

IF(LIBRNN_USE_LOG4CPP_OUTPUT)
  target_link_libraries(librnnUnitTest    rnn log4cpp)
  target_link_libraries(librnnRuntimeTest rnn log4cpp)
  message("linking log4cpp to test programs")
ELSE(LIBRNN_USE_LOG4CPP_OUTPUT)
  message("NOT linking log4cpp to test programs")
ENDIF(LIBRNN_USE_LOG4CPP_OUTPUT)



