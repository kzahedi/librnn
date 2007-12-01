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




IF(LIBRNN_DEBUG)
  set(CMAKE_BUILD_TYPE Debug)
else(LIBRNN_DEBUG)
  set(CMAKE_BUILD_TYPE Relase)
ENDIF(LIBRNN_DEBUG)
