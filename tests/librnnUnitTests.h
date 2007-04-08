#ifndef __LIBRNN_TEST_H__
#define __LIBRNN_TEST_H__

#include <cppunit/extensions/HelperMacros.h>

class librnnUnitTests : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( librnnUnitTests );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testTransferfunction );
  CPPUNIT_TEST( testSingleNeuronWithOscillation );
  CPPUNIT_TEST( testNoTransferfunctionException );
  CPPUNIT_TEST( testRecurrentNeuralNetworkWithSingleNeuron );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void testConstructor();
  void testTransferfunction();
  void testSingleNeuronWithOscillation();
  void testNoTransferfunctionException();
  void testRecurrentNeuralNetworkWithSingleNeuron();
};

#endif // __LIBRNN_TEST_H__
