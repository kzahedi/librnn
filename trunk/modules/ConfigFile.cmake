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
