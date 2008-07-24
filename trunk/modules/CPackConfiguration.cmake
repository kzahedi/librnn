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



INCLUDE(InstallRequiredSystemLibraries)
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "librnn - Library for Recurrent Neural Networks")
SET(CPACK_PACKAGE_VENDOR "Keyan")
SET(CPACK_GENERATOR "TBZ2;ZIP")
SET(CPACK_SOURCE_GENERATOR "STGZ;TBZ2;ZIP")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
#SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.txt")
#SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
SET(CPACK_PACKAGE_VERSION_MAJOR "${LIBRNN_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${LIBRNN_MINOR}")
IF(LIBRNN_INCR IS NOT "0")
SET(CPACK_PACKAGE_VERSION_PATCH "${LIBRNN_INCR}-${LIBRNN_PATCH}")
ELSE(LIBRNN_INCR IS NOT "0")
SET(CPACK_PACKAGE_VERSION_PATCH "${LIBRNN_INCR}")
ENDIF(LIBRNN_INCR IS NOT "0")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "${LIBRNN_TARGET} ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
SET(CPACK_SYSTEM_NAME "${CMAKE_SYSTEM}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "/usr/local")
set(CPACK_SOURCE_IGNORE_FILES "^${PROJECT_SOURCE_DIR}/old/;.svn;*.swp")
INCLUDE(CPack)
