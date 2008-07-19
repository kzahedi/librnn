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
  CPPUNIT_ASSERT_EQUAL(rnn->getNeuronCount(), 0);
  delete rnn;
}

void librnnUnitTests::testTransferfunction()
{
  __REAL testActivation = 0.0;
  RecurrentNeuralNetwork *rnn = new RecurrentNeuralNetwork();
  Neuron *neuron = new Neuron();
  neuron->setActivation(testActivation);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(neuron->getActivation(), testActivation,0.0000000001);
  neuron->setTransferfunction(&transferfunction_tanh);
  rnn->updateOutput(neuron);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(transferfunction_tanh(testActivation), neuron->getActivation(), 0.0000000001);
  
  testActivation = 1.0;
  neuron->setActivation(testActivation);
  rnn->updateOutput(neuron);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(neuron->getOutput(), transferfunction_tanh(testActivation),0.0000000001);

  neuron->setTransferfunction(&transferfunction_id);
  rnn->updateOutput(neuron);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(neuron->getOutput(), transferfunction_id(testActivation),0.0000000001);

  testActivation = -1.0;
  neuron->setActivation(testActivation);
  neuron->setTransferfunction(&transferfunction_tanh);
  rnn->updateOutput(neuron);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(neuron->getOutput(), transferfunction_tanh(testActivation),0.0000000001);

  neuron->setTransferfunction(&transferfunction_id);
  rnn->updateOutput(neuron);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(neuron->getOutput(), transferfunction_id(testActivation),0.0000000001);

  delete neuron;
}


void librnnUnitTests::testSingleNeuronWithOscillation()
{
  RecurrentNeuralNetwork *rnn = new RecurrentNeuralNetwork();
  Neuron  *neuron  = new Neuron();
  Synapse *synapse = new Synapse(neuron, neuron, -5);
  rnn->add(neuron);
  rnn->add(synapse);
  neuron->setTransferfunction(transferfunction_tanh);
  neuron->setActivation(1.0);
  rnn->updateOutput(neuron);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(transferfunction_tanh(1.0),rnn->getOutput(neuron),0.0000000001);
  for(int i=0; i < 100; i++)
  {
    rnn->updateActivation(neuron);
    rnn->updateOutput(neuron);
  }

  if(rnn->getOutput(neuron) < 0)
  {
    rnn->updateActivation(neuron);
    rnn->updateOutput(neuron);
  }

  CPPUNIT_ASSERT_EQUAL(1, rnn->getSynapsesCount(neuron));

  CPPUNIT_ASSERT_DOUBLES_EQUAL(-5.0, rnn->getSynapse(neuron, 0)->strength(), 0.01);

  //check for oscillation
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, rnn->getOutput(neuron), 0.01);
  rnn->updateActivation(neuron);
  rnn->updateOutput(neuron);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, rnn->getOutput(neuron), 0.01);
  rnn->updateActivation(neuron);
  rnn->updateOutput(neuron);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, rnn->getOutput(neuron), 0.01);
  rnn->updateActivation(neuron);
  rnn->updateOutput(neuron);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, rnn->getOutput(neuron), 0.01);
  rnn->updateActivation(neuron);
  rnn->updateOutput(neuron);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, rnn->getOutput(neuron), 0.01);
}


void librnnUnitTests::testNoTransferfunctionException()
{
  RecurrentNeuralNetwork *rnn   = new RecurrentNeuralNetwork();
  Neuron *neuron   = new Neuron();
  neuron->setActivation(1.0);
  try
  {
    rnn->updateOutput(neuron);
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
  rnn->add(neuron);
  rnn->add(s);

  CPPUNIT_ASSERT_EQUAL(1, rnn->getSynapsesCount());
  CPPUNIT_ASSERT_EQUAL(1, rnn->getSynapsesCount(neuron));
  CPPUNIT_ASSERT_EQUAL(1, rnn->countSynapses());

  neuron->setActivation(-10);
  rnn->updateOutput(neuron);
  rnn->updateActivation(neuron);
  rnn->updateOutput(neuron);

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

#ifdef TIME_CONSUMING_TEST
void librnnUnitTests::testSmallNeuroModule()
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.setPriority(log4cpp::Priority::DEBUG);
#endif // USE_LOG4CPP_OUTPUT

  RecurrentNeuralNetwork *rnn = new RecurrentNeuralNetwork();
  Neuron  *inputNeuron = new Neuron();
  Neuron  *outputNeuron = new Neuron();
  Synapse *woi = new Synapse(inputNeuron,  outputNeuron,  2.0);
  Synapse *woo = new Synapse(outputNeuron, outputNeuron, -2.5);

  inputNeuron->setTransferfunction(&transferfunction_id);
  outputNeuron->setTransferfunction(&transferfunction_tanh);
  rnn->add(inputNeuron);
  rnn->add(outputNeuron);
  rnn->add(woi);
  rnn->add(woo);

  CPPUNIT_ASSERT_EQUAL(1, rnn->getSynapsesCount(inputNeuron));
  CPPUNIT_ASSERT_EQUAL(2, rnn->getSynapsesCount(outputNeuron));

  CPPUNIT_ASSERT_EQUAL(1, rnn->getAdjacentSynapsesCount(inputNeuron));
  CPPUNIT_ASSERT_EQUAL(0, rnn->getIncidentSynapsesCount(inputNeuron));

  CPPUNIT_ASSERT_EQUAL(1, rnn->getAdjacentSynapsesCount(outputNeuron));
  CPPUNIT_ASSERT_EQUAL(2, rnn->getIncidentSynapsesCount(outputNeuron));
  rnn->update();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, inputNeuron->getOutput(), 0.00001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, outputNeuron->getOutput(), 0.00001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, inputNeuron->getActivation(), 0.00001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, outputNeuron->getActivation(), 0.00001);

  __REAL output = 0;
  __REAL bias   = -1;
  __REAL delta  = 2.0 / 1000.0;

  // mini bifurcation diagram test
  for(int i=0; i < 1000; i++)
  {
    inputNeuron->setBias(bias);
    rnn->updateActivation(inputNeuron);
    rnn->updateOutput(inputNeuron);
    for(int j=0; j < 10000; j++)
    {
      rnn->update();
      output = transferfunction_tanh( -2.5 * output + 2.0 * bias);
#ifdef USE_LOG4CPP_OUTPUT
      libRnnLogger.debug("rnn->update: %f vs. %f", outputNeuron->getOutput(), output);
#endif
    }
    bias += delta;
  }
  CPPUNIT_ASSERT_DOUBLES_EQUAL(output, outputNeuron->getOutput(), 0.000001);
}
#endif


void librnnUnitTests::testAddingAndDeletingOfSynapses()
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.setPriority(log4cpp::Priority::DEBUG);
#endif // USE_LOG4CPP_OUTPUT

  RecurrentNeuralNetwork *rnn = new RecurrentNeuralNetwork();
  Neuron  *neuron = new Neuron();
  Synapse *woo = new Synapse(neuron, neuron, -100);
  Synapse *w1 = new Synapse(neuron, neuron, -100);
  Synapse *w2 = new Synapse(neuron, neuron, -100);
  Synapse *w3 = new Synapse(neuron, neuron, -100);
  Synapse *w4 = new Synapse(neuron, neuron, -100);
  Synapse *w5 = new Synapse(neuron, neuron, -100);

  neuron->setTransferfunction(&transferfunction_tanh);
  rnn->add(neuron);
  rnn->add(woo);

  CPPUNIT_ASSERT_EQUAL(1, rnn->getSynapsesCount());
  CPPUNIT_ASSERT_EQUAL(1, rnn->getSynapsesCount(neuron));
  CPPUNIT_ASSERT_EQUAL(1, rnn->countSynapses());

  neuron->setActivation(-10);
  rnn->updateOutput(neuron);
  rnn->updateActivation(neuron);
  rnn->updateOutput(neuron);

  //CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, neuron->getOutput(), 0.00001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, neuron->getOutput(), 0.00001);

  rnn->update();

  CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.00, neuron->getOutput(), 0.00001);

  rnn->remove(woo);
  CPPUNIT_ASSERT_EQUAL(0, rnn->getSynapsesCount(neuron));

  rnn->add(w1);
  rnn->add(w2);
  rnn->add(w3);
  rnn->add(w4);
  rnn->add(w5);

#ifdef USE_VECTOR
  CPPUNIT_ASSERT_EQUAL(5, rnn->getSynapsesCount());
  CPPUNIT_ASSERT_EQUAL(5, rnn->getSynapsesCount(neuron));
  CPPUNIT_ASSERT_EQUAL(5, rnn->countSynapses());
#endif // USE_VECTOR
#ifdef USE_MATRIX
  CPPUNIT_ASSERT_EQUAL(1, rnn->getSynapsesCount());
  CPPUNIT_ASSERT_EQUAL(1, rnn->getSynapsesCount(neuron));
  CPPUNIT_ASSERT_EQUAL(1, rnn->countSynapses());
#endif // USE_MATRIX

  rnn->remove(w2);
#ifdef USE_VECTOR
  CPPUNIT_ASSERT_EQUAL(4, rnn->getSynapsesCount());
  CPPUNIT_ASSERT_EQUAL(4, rnn->getSynapsesCount(neuron));
  CPPUNIT_ASSERT_EQUAL(4, rnn->countSynapses());
#endif // USE_VECTOR
#ifdef USE_MATRIX
  CPPUNIT_ASSERT_EQUAL(1, rnn->getSynapsesCount());
  CPPUNIT_ASSERT_EQUAL(1, rnn->getSynapsesCount(neuron));
  CPPUNIT_ASSERT_EQUAL(1, rnn->countSynapses());
#endif // USE_MATRIX

  rnn->remove(w3);
#ifdef USE_VECTOR
  CPPUNIT_ASSERT_EQUAL(3, rnn->getSynapsesCount());
  CPPUNIT_ASSERT_EQUAL(3, rnn->getSynapsesCount(neuron));
  CPPUNIT_ASSERT_EQUAL(3, rnn->countSynapses());
#endif // USE_VECTOR
#ifdef USE_MATRIX
  CPPUNIT_ASSERT_EQUAL(1, rnn->getSynapsesCount());
  CPPUNIT_ASSERT_EQUAL(1, rnn->getSynapsesCount(neuron));
  CPPUNIT_ASSERT_EQUAL(1, rnn->countSynapses());
#endif // USE_MATRIX

  rnn->remove(w1);
#ifdef USE_VECTOR
  CPPUNIT_ASSERT_EQUAL(2, rnn->getSynapsesCount());
  CPPUNIT_ASSERT_EQUAL(2, rnn->getSynapsesCount(neuron));
  CPPUNIT_ASSERT_EQUAL(2, rnn->countSynapses());
#endif // USE_VECTOR
#ifdef USE_MATRIX
  CPPUNIT_ASSERT_EQUAL(1, rnn->getSynapsesCount());
  CPPUNIT_ASSERT_EQUAL(1, rnn->getSynapsesCount(neuron));
  CPPUNIT_ASSERT_EQUAL(1, rnn->countSynapses());
#endif // USE_MATRIX

  rnn->remove(w4);
#ifdef USE_VECTOR
  CPPUNIT_ASSERT_EQUAL(1, rnn->getSynapsesCount());
  CPPUNIT_ASSERT_EQUAL(1, rnn->getSynapsesCount(neuron));
  CPPUNIT_ASSERT_EQUAL(1, rnn->countSynapses());
#endif // USE_VECTOR
#ifdef USE_MATRIX
  CPPUNIT_ASSERT_EQUAL(1, rnn->getSynapsesCount());
  CPPUNIT_ASSERT_EQUAL(1, rnn->getSynapsesCount(neuron));
  CPPUNIT_ASSERT_EQUAL(1, rnn->countSynapses());
#endif // USE_MATRIX

  rnn->remove(w5);
  CPPUNIT_ASSERT_EQUAL(0, rnn->getSynapsesCount());
  CPPUNIT_ASSERT_EQUAL(0, rnn->getSynapsesCount(neuron));
  CPPUNIT_ASSERT_EQUAL(0, rnn->countSynapses());
}

void librnnUnitTests::testAddingAndDeletingOfNeuronsWithNoSynapses()
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.setPriority(log4cpp::Priority::DEBUG);
#endif // USE_LOG4CPP_OUTPUT

  RecurrentNeuralNetwork *rnn = new RecurrentNeuralNetwork();
  Neuron  *n1 = new Neuron();
  Neuron  *n2 = new Neuron();
  Neuron  *n3 = new Neuron();
  Neuron  *n4 = new Neuron();
  Neuron  *n5 = new Neuron();

  rnn->add(n1);
  rnn->add(n2);
  rnn->add(n3);
  rnn->add(n4);
  rnn->add(n5);

  CPPUNIT_ASSERT_EQUAL(5, rnn->getNeuronCount());

  rnn->remove(n1);

  CPPUNIT_ASSERT_EQUAL(4, rnn->getNeuronCount());

  CPPUNIT_ASSERT_EQUAL(n2, rnn->getNeuron(0));
  CPPUNIT_ASSERT_EQUAL(n3, rnn->getNeuron(1));
  CPPUNIT_ASSERT_EQUAL(n4, rnn->getNeuron(2));
  CPPUNIT_ASSERT_EQUAL(n5, rnn->getNeuron(3));

  rnn->remove(n3);

  CPPUNIT_ASSERT_EQUAL(n2, rnn->getNeuron(0));
  CPPUNIT_ASSERT_EQUAL(n4, rnn->getNeuron(1));
  CPPUNIT_ASSERT_EQUAL(n5, rnn->getNeuron(2));

  rnn->remove(n4);

  CPPUNIT_ASSERT_EQUAL(n2, rnn->getNeuron(0));
  CPPUNIT_ASSERT_EQUAL(n5, rnn->getNeuron(1));


}

void librnnUnitTests::testAddingAndDeletingOfNeurons()
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.setPriority(log4cpp::Priority::DEBUG);
#endif // USE_LOG4CPP_OUTPUT

  RecurrentNeuralNetwork *rnn = new RecurrentNeuralNetwork();
  Neuron  *n1 = new Neuron();
  Neuron  *n2 = new Neuron();
  Neuron  *n3 = new Neuron();
  Neuron  *n4 = new Neuron();
  Neuron  *n5 = new Neuron();

  Synapse *w51 = new Synapse(n1, n5, 1);
  Synapse *w55 = new Synapse(n5, n5, 1);
  Synapse *w52 = new Synapse(n2, n5, 1);

  Synapse *w44 = new Synapse(n4, n4, 1);
  Synapse *w41 = new Synapse(n1, n4, 1);
  Synapse *w42 = new Synapse(n2, n4, 1);
  Synapse *w43 = new Synapse(n3, n4, 1);

  Synapse *w14 = new Synapse(n4, n1, 1);

  Synapse *w22 = new Synapse(n2, n2, 1);
  Synapse *w21 = new Synapse(n1, n2, 1);

  Synapse *w31 = new Synapse(n1, n3, 1);
  Synapse *w32 = new Synapse(n2, n3, 1);
  Synapse *w33 = new Synapse(n3, n3, 1);
  Synapse *w34 = new Synapse(n4, n3, 1);
  Synapse *w35 = new Synapse(n5, n3, 1);

  rnn->add(n1);
  rnn->add(n2);
  rnn->add(n3);
  rnn->add(n4);
  rnn->add(n5);

  rnn->add(w51);
  rnn->add(w55);
  rnn->add(w52);
  rnn->add(w44);
  rnn->add(w41);
  rnn->add(w42);
  rnn->add(w43);
  rnn->add(w14);
  rnn->add(w22);
  rnn->add(w21);
  rnn->add(w31);
  rnn->add(w32);
  rnn->add(w33);
  rnn->add(w34);
  rnn->add(w35);

  CPPUNIT_ASSERT_EQUAL(5, rnn->getNeuronCount());

  CPPUNIT_ASSERT_EQUAL(15, rnn->getSynapsesCount());
  CPPUNIT_ASSERT_EQUAL(26, rnn->countSynapses());

  CPPUNIT_ASSERT_EQUAL(4, rnn->getSynapsesCount(n5));
  CPPUNIT_ASSERT_EQUAL(6, rnn->getSynapsesCount(n4));
  CPPUNIT_ASSERT_EQUAL(6, rnn->getSynapsesCount(n3));
  CPPUNIT_ASSERT_EQUAL(5, rnn->getSynapsesCount(n2));
  CPPUNIT_ASSERT_EQUAL(5, rnn->getSynapsesCount(n1));

  CPPUNIT_ASSERT_EQUAL(3, rnn->getIncidentSynapsesCount(n5));
  CPPUNIT_ASSERT_EQUAL(4, rnn->getIncidentSynapsesCount(n4));
  CPPUNIT_ASSERT_EQUAL(5, rnn->getIncidentSynapsesCount(n3));
  CPPUNIT_ASSERT_EQUAL(2, rnn->getIncidentSynapsesCount(n2));
  CPPUNIT_ASSERT_EQUAL(1, rnn->getIncidentSynapsesCount(n1));

  CPPUNIT_ASSERT_EQUAL(2, rnn->getAdjacentSynapsesCount(n5));
  CPPUNIT_ASSERT_EQUAL(3, rnn->getAdjacentSynapsesCount(n4));
  CPPUNIT_ASSERT_EQUAL(2, rnn->getAdjacentSynapsesCount(n3));
  CPPUNIT_ASSERT_EQUAL(4, rnn->getAdjacentSynapsesCount(n2));
  CPPUNIT_ASSERT_EQUAL(4, rnn->getAdjacentSynapsesCount(n1));

  rnn->remove(n1);

  CPPUNIT_ASSERT_EQUAL(4, rnn->getNeuronCount());
  CPPUNIT_ASSERT_EQUAL(10, rnn->getSynapsesCount());
  CPPUNIT_ASSERT_EQUAL(4, rnn->getSynapsesCount(n4));
  CPPUNIT_ASSERT_EQUAL(5, rnn->getSynapsesCount(n3));
  CPPUNIT_ASSERT_EQUAL(4, rnn->getSynapsesCount(n2));

  CPPUNIT_ASSERT_EQUAL(2, rnn->getIncidentSynapsesCount(n5));
  CPPUNIT_ASSERT_EQUAL(3, rnn->getIncidentSynapsesCount(n4));
  CPPUNIT_ASSERT_EQUAL(4, rnn->getIncidentSynapsesCount(n3));
  CPPUNIT_ASSERT_EQUAL(1, rnn->getIncidentSynapsesCount(n2));

  CPPUNIT_ASSERT_EQUAL(2, rnn->getAdjacentSynapsesCount(n5));
  CPPUNIT_ASSERT_EQUAL(2, rnn->getAdjacentSynapsesCount(n4));
  CPPUNIT_ASSERT_EQUAL(2, rnn->getAdjacentSynapsesCount(n3));
  CPPUNIT_ASSERT_EQUAL(4, rnn->getAdjacentSynapsesCount(n2));

  CPPUNIT_ASSERT_EQUAL(10, rnn->getSynapsesCount());
  CPPUNIT_ASSERT_EQUAL(16, rnn->countSynapses());

  CPPUNIT_ASSERT_EQUAL(16, rnn->countSynapses());

  CPPUNIT_ASSERT_EQUAL(3, rnn->getSynapsesCount(n5));
}
