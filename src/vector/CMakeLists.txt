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



add_library(rnnVector SHARED Neuron.cpp RecurrentNeuralNetwork.cpp Synapse.cpp)
include_directories("${PROJECT_SOURCE_DIR}/include/" "${PROJECT_BINARY_DIR}/include/")

if(LIBRNN_USE_LOG4CPP_OUTPUT)
  target_link_libraries(rnnVector log4cpp)
  message("linking log4cpp to rnn")
  message("NOT linking log4cpp to test programs")
else(LIBRNN_USE_LOG4CPP_OUTPUT)
  message("NOT linking log4cpp to librnn")
endif(LIBRNN_USE_LOG4CPP_OUTPUT)

ADD_DEFINITIONS(-DUSE_VECTOR)


