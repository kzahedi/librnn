#include "librnnUnitTests.h"
#include "librnn/defines.h"
#include "librnn/RecurrentNeuralNetwork.h"
#include "librnn/transferfunctions.h"

#include <math.h>
#include <iostream>

using namespace librnn;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( librnnUnitTests );


void librnnUnitTests::setUp()
{ }


void librnnUnitTests::tearDown()
{ }


void librnnUnitTests::testConstructor()
{
  RecurrentNeuralNetwork *rnn = new RecurrentNeuralNetwork();

//  CPPUNIT_ASSERT_EQUAL(rnn->getNumberOfSynapses(), -1);
  CPPUNIT_ASSERT_EQUAL(rnn->getNumberOfNeurons(), 0);

  delete rnn;
}

void librnnUnitTests::testTransferfunction()
{
  REAL testActivation = 0.0;
  Neuron *neuron = new Neuron();
  neuron->setActivation(testActivation);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(neuron->getActivation(), testActivation,0.0000000001);
  neuron->setTransferfunction(&transferfunction_tanh);
  neuron->updateOutput();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(neuron->getActivation(), transferfunction_tanh(testActivation),0.0000000001);
  
  testActivation = 1.0;
  neuron->setActivation(testActivation);
  neuron->updateOutput();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(neuron->getOutput(), transferfunction_tanh(testActivation),0.0000000001);

  neuron->setTransferfunction(transferfunction_id);
  neuron->updateOutput();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(neuron->getOutput(), (testActivation),0.0000000001);

  testActivation = -1.0;
  neuron->setActivation(testActivation);
  neuron->setTransferfunction(&transferfunction_tanh);
  neuron->updateOutput();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(neuron->getOutput(), transferfunction_tanh(testActivation),0.0000000001);

  neuron->setTransferfunction(transferfunction_id);
  neuron->updateOutput();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(neuron->getOutput(), (testActivation),0.0000000001);

  delete neuron;
}


void librnnUnitTests::testSingleNeuronWithOscillation()
{
  Neuron *neuron   = new Neuron();
  Synapse *synapse = new Synapse(neuron, neuron, -5);
  neuron->addSynapse(synapse);
  neuron->setTransferfunction(transferfunction_tanh);
  neuron->setActivation(1.0);
  neuron->updateOutput();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(neuron->getOutput(), transferfunction_tanh(1.0),0.0000000001);
  for(int i=0; i < 100; i++)
  {
    neuron->updateActivation();
    neuron->updateOutput();
  }

  if(neuron->getOutput() < 0)
  {
    neuron->updateActivation();
    neuron->updateOutput();
  }

  //check for oscillation
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, neuron->getOutput(), 0.01);
  neuron->updateActivation();
  neuron->updateOutput();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(neuron->getOutput(), -1.0, 0.01);
  neuron->updateActivation();
  neuron->updateOutput();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(neuron->getOutput(), 1.0, 0.01);
  neuron->updateActivation();
  neuron->updateOutput();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(neuron->getOutput(), -1.0, 0.01);
  neuron->updateActivation();
  neuron->updateOutput();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(neuron->getOutput(), 1.0, 0.01);

  delete neuron;
  delete synapse;
}


void librnnUnitTests::testNoTransferfunctionException()
{
  Neuron *neuron   = new Neuron();
  neuron->setActivation(1.0);
  try
  {
    neuron->updateOutput();
    CPPUNIT_FAIL("no exception thrown");
  }
  catch(librnn::NeuronException ne)
  {
    delete neuron;
    return;
  }
}



void librnnUnitTests::testRecurrentNeuralNetworkWithSingleNeuron()
{
  // create single neuron without recurrent neural network interface as control
  Neuron *neuron   = new Neuron();
  Synapse *synapse = new Synapse(neuron, neuron, -5);
  neuron->addSynapse(synapse);
  neuron->setTransferfunction(transferfunction_tanh);
  neuron->setActivation(1.0);
  neuron->updateOutput();

  RecurrentNeuralNetwork *rnn = new RecurrentNeuralNetwork();
  Neuron *n  = new Neuron();
  Synapse *s = new Synapse(neuron, neuron, -5);
  rnn->addNeuron(n);
  rnn->addSynapse(s);
  CPPUNIT_ASSERT_EQUAL(1, rnn->countSynapses());
  CPPUNIT_ASSERT_EQUAL(1, rnn->getSynapsesCount());
}
