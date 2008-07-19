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



IF(LIBRNN_DOUBLE_PRECISION)
  set(USE_DOUBLE_PRECISION 1)
else(LIBRNN_DOUBLE_PRECISION)
  set(USE_FLOAT_PRECISION 1)
ENDIF(LIBRNN_DOUBLE_PRECISION)

IF(LIBRNN_USE_LOG4CPP_OUTPUT)
  set(USE_LOG4CPP_OUTPUT 1)
endif(LIBRNN_USE_LOG4CPP_OUTPUT)

IF(LIBRNN_USE_ONLY_FAST_TESTS)
ELSE(LIBRNN_USE_ONLY_FAST_TESTS)
  set(TIME_CONSUMING_TEST 1)
endif(LIBRNN_USE_ONLY_FAST_TESTS)

IF(LIBRNN_DESIGN_BY_CONTRACT)
  set(DESIGN_BY_CONTRACT 1)
endif(LIBRNN_DESIGN_BY_CONTRACT)

CONFIGURE_FILE(config.h.cmake "${PROJECT_BINARY_DIR}/include/librnn/config.h")
