INCLUDE(InstallRequiredSystemLibraries)
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "librnn - Library for Recurrent Neural Networks")
SET(CPACK_PACKAGE_VENDOR "Keyan")
SET(CPACK_GENERATOR "STGZ;TBZ2;ZIP")
SET(CPACK_SOURCE_GENERATOR "STGZ;TBZ2;ZIP")
#SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.txt")
#SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
SET(CPACK_PACKAGE_VERSION_MAJOR "${LIBRNN_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${LIBRNN_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${LIBRNN_PATCH}")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "${LIBRNN_TARGET} ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
SET(CPACK_SYSTEM_NAME "${CMAKE_SYSTEM}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "/usr/local")
set(CPACK_SOURCE_IGNORE_FILES "/CVS/;/.svn/;.swp$;.#;/#;.*~;cscope.*")
INCLUDE(CPack)
