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


