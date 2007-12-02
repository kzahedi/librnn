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



# Rules for the test code (use `make check` to execute)
TESTS = librnnTestSuite librnnRuntimeTest
check_PROGRAMS = $(TESTS)
librnnTestSuite_SOURCES = LibRnnTest.cpp testMain.cpp
librnnTestSuite_CXXFLAGS = $(CPPUNIT_CFLAGS) -I../include
librnnTestSuite_LDFLAGS = $(CPPUNIT_LIBS) -ldl -L../src -lrnn

bin_PROGRAMS = librnnRuntimeTest
librnnRuntimeTest_SOURCES = librnnRuntimeTestMain.cpp
librnnRuntimeTest_CXXFLAGS =  -I../include -I$(LD_INCLUDE_PATH)
librnnRuntimeTest_LDFLAGS = -L../src -lrnn -lstopwatch


