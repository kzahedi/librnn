#ifndef __LIBRNN_TEST_H__
#define __LIBRNN_TEST_H__

#include <cppunit/extensions/HelperMacros.h>

class LibRnnTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( LibRnnTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testTransferfunction );
  CPPUNIT_TEST( testSingleNeuronWithOscillation );
  CPPUNIT_TEST( testNoTransferfunctionException );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void testConstructor();
  void testTransferfunction();
  void testSingleNeuronWithOscillation();
  void testNoTransferfunctionException();
};

#endif // __LIBRNN_TEST_H__
