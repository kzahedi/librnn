message("> Debug configuration: Compilation")
IF(LIBRNN_DEBUG)
  message("--> compiling in librnn in DEBUG mode.")
else(LIBRNN_DEBUG)
  message("--> compiling in librnn in RELEASE mode.")
ENDIF(LIBRNN_DEBUG)

message("> Debug configuration: log4cpp")
IF(LIBRNN_USE_LOG4CPP_OUTPUT)
  message("USING log4cpp support.")
ELSE(LIBRNN_USE_LOG4CPP_OUTPUT)
  message("OMITTING log4cpp support.")
endif(LIBRNN_USE_LOG4CPP_OUTPUT)

message("> Implementation configuration: Model")
IF(LIBRNN_IMPLEMENTATION_MODE MATCHES ADJANCENY_LIST)
  message("--> using adjacency LIST implementation.")
endif(LIBRNN_IMPLEMENTATION_MODE MATCHES ADJANCENY_LIST)

IF(LIBRNN_IMPLEMENTATION_MODE MATCHES ADJANCENY_VECTOR)
  message("--> using adjacency VECTOR implementation.")
endif(LIBRNN_IMPLEMENTATION_MODE MATCHES ADJANCENY_VECTOR)

message("> Implementation configuration: Precision")
IF(LIBRNN_DOUBLE_PRECISION)
  message("Building using DOUBLE precision.")
else(LIBRNN_DOUBLE_PRECISION)
  message("Building using FLOAT precision.")
endif(LIBRNN_DOUBLE_PRECISION)

message("> Build options: Unit tests.")
IF(LIBRNN_USE_ONLY_FAST_TESTS)
  message("--> only testing with FAST tests.")
else(LIBRNN_USE_ONLY_FAST_TESTS)
  message("--> using ALL unit tests.")
endif(LIBRNN_USE_ONLY_FAST_TESTS)

message("> values")
message("LIBRNN_DEBUG:               ${LIBRNN_DEBUG}")
message("LIBRNN_USE_LOG4CPP_OUTPUT:  ${LIBRNN_USE_LOG4CPP_OUTPUT}")
message("LIBRNN_IMPLEMENTATION_MODE: ${LIBRNN_IMPLEMENTATION_MODE}")
message("LIBRNN_DOUBLE_PRECISION:    ${LIBRNN_DOUBLE_PRECISION}")
message("LIBRNN_USE_ONLY_FAST_TESTS: ${LIBRNN_USE_ONLY_FAST_TESTS}")

message("USE_DOUBLE_PRECISION:       ${USE_DOUBLE_PRECISION}")
message("IMPL_ADJ_LIST:              ${IMPL_ADJ_LIST}")
message("IMPL_ADJ_VECTOR:            ${IMPL_ADJ_VECTOR}")
message("USE_LOG4CPP_OUTPUT:         ${USE_LOG4CPP_OUTPUT}")
message("TIME_CONSUMING_TEST:        ${TIME_CONSUMING_TEST}")

message("> END")
