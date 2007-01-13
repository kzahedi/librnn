#include "LibRnnTest.h"
#include "librnn/RecurrentNeuralNetwork.h"

using namespace librnn;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( LibRnnTest );


void LibRnnTest::setUp()
{ }


void LibRnnTest::tearDown()
{ }


void LibRnnTest::testConstructor()
{
  RecurrentNeuralNetwork *rnn = new RecurrentNeuralNetwork();

  CPPUNIT_ASSERT_EQUAL(rnn->getNumberOfSynapses(), -1);
  CPPUNIT_ASSERT_EQUAL(rnn->getNumberOfNeurons(), -1);

  delete rnn;
}

