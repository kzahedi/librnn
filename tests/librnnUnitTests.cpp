/**************************************************************************
 *                                                                        *
 * This file is part of librnn. Copyright (C) 2003-2006 Keyan Zahedi.     *
 * All rights reserved. Email: keyan@users.sourceforge.net                *
 * Web: http://sourceforge.net/projects/librnn                            *
 *                                                                        *
 * For a list of contributors see the file AUTHORS.                       *
 *                                                                        *
 * librnn is free software; you can redistribute it and/or modify it      *
 * under the terms of the GNU General Public License as published by the  *
 * Free Software Foundation; either version 2 of the License, or (at      *
 * your option) any later version.                                        *
 *                                                                        *
 * librnn is distributed in the hope that it will be useful, but WITHOUT  *
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or  *
 * FITNESS FOR A PARTICULAR PURPOSE.                                      *
 *                                                                        *
 * You should have received a copy of the GNU General Public License      *
 * along with librnn in the file COPYING; if not, write to the Free       *
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA     *
 * 02110-1301, USA.                                                       *
 *                                                                        *
 **************************************************************************/



#include <librnnUnitTests.h>
#include <librnn/librnn.h>

#include <math.h>
#include <iostream>

using namespace librnn;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( librnnUnitTests );


void librnnUnitTests::setUp()
{
#ifdef USE_LOG4CPP_OUTPUT
  initLogger();
#endif
}


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

  neuron->setTransferfunction(&transferfunction_id);
  neuron->updateOutput();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(neuron->getOutput(), transferfunction_id(testActivation),0.0000000001);

  testActivation = -1.0;
  neuron->setActivation(testActivation);
  neuron->setTransferfunction(&transferfunction_tanh);
  neuron->updateOutput();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(neuron->getOutput(), transferfunction_tanh(testActivation),0.0000000001);

  neuron->setTransferfunction(&transferfunction_id);
  neuron->updateOutput();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(neuron->getOutput(), transferfunction_id(testActivation),0.0000000001);

  delete neuron;
}


void librnnUnitTests::testSingleNeuronWithOscillation()
{
  Neuron  *neuron  = new Neuron();
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

  CPPUNIT_ASSERT_EQUAL(1, neuron->getSynapsesCount());

  CPPUNIT_ASSERT_DOUBLES_EQUAL(-5.0, neuron->getSynapse(0)->strength(), 0.01);

  //check for oscillation
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, neuron->getOutput(), 0.01);
  neuron->updateActivation();
  neuron->updateOutput();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, neuron->getOutput(), 0.01);
  neuron->updateActivation();
  neuron->updateOutput();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, neuron->getOutput(), 0.01);
  neuron->updateActivation();
  neuron->updateOutput();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, neuron->getOutput(), 0.01);
  neuron->updateActivation();
  neuron->updateOutput();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, neuron->getOutput(), 0.01);

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
  RecurrentNeuralNetwork *rnn = new RecurrentNeuralNetwork();
  Neuron  *neuron = new Neuron();
  Synapse *s = new Synapse(neuron, neuron, -5);

  neuron->setTransferfunction(&transferfunction_tanh);
  rnn->addNeuron(neuron);
  rnn->addSynapse(s);

  CPPUNIT_ASSERT_EQUAL(1, rnn->getSynapsesCount());
  CPPUNIT_ASSERT_EQUAL(1, neuron->getSynapsesCount());
  CPPUNIT_ASSERT_EQUAL(1, rnn->countSynapses());

  neuron->setActivation(-10);
  neuron->updateOutput();
  neuron->updateActivation();
  neuron->updateOutput();

  rnn->update();

  for(int i=0; i < 100; i++)
  {
    rnn->update();
  }

  if(neuron->getOutput() < 0)
  {
    rnn->update();
  }

  //check for oscillation
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, neuron->getOutput(), 0.01);
  rnn->update();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, neuron->getOutput(), 0.01);
  rnn->update();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, neuron->getOutput(), 0.01);
  rnn->update();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, neuron->getOutput(), 0.01);
  rnn->update();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, neuron->getOutput(), 0.01);

}


void librnnUnitTests::testSmallNeuroModule()
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.setPriority(log4cpp::Priority::FATAL);
#endif // USE_LOG4CPP_OUTPUT

  RecurrentNeuralNetwork *rnn = new RecurrentNeuralNetwork();
  Neuron  *inputNeuron = new Neuron();
  Neuron  *outputNeuron = new Neuron();
  Synapse *woi = new Synapse(inputNeuron,  outputNeuron,  2.0);
  Synapse *woo = new Synapse(outputNeuron, outputNeuron, -2.5);

  inputNeuron->setTransferfunction(&transferfunction_id);
  outputNeuron->setTransferfunction(&transferfunction_tanh);
  rnn->addNeuron(inputNeuron);
  rnn->addNeuron(outputNeuron);
  rnn->addSynapse(woi);
  rnn->addSynapse(woo);

  CPPUNIT_ASSERT_EQUAL(1, inputNeuron->getSynapsesCount());
  CPPUNIT_ASSERT_EQUAL(2, outputNeuron->getSynapsesCount());

  CPPUNIT_ASSERT_EQUAL(1, inputNeuron->getAdjacentSynapsesCount());
  CPPUNIT_ASSERT_EQUAL(0, inputNeuron->getIncidentSynapsesCount());

  CPPUNIT_ASSERT_EQUAL(1, outputNeuron->getAdjacentSynapsesCount());
  CPPUNIT_ASSERT_EQUAL(2, outputNeuron->getIncidentSynapsesCount());
  rnn->update();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, inputNeuron->getOutput(), 0.00001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, outputNeuron->getOutput(), 0.00001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, inputNeuron->getActivation(), 0.00001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, outputNeuron->getActivation(), 0.00001);


  REAL output = 0;
  REAL bias   = -1;
  REAL delta  = 2.0 / 1000.0;

  // mini bifurcation diagram test
  for(int i=0; i < 1000; i++)
  {
    inputNeuron->setBias(bias);
    inputNeuron->updateActivation();
    inputNeuron->updateOutput();
    for(int j=0; j < 1000; j++)
    {
      rnn->update();
      output = transferfunction_tanh( -2.5 * output + 2.0 * bias);
      libRnnLogger.debug("rnn->update: %f vs. %f", outputNeuron->getOutput(), output);
      //cout << "test " << j << " " << i << endl;
    }
    bias += delta;
  }
  CPPUNIT_ASSERT_DOUBLES_EQUAL(output, outputNeuron->getOutput(), 0.000001);

}
