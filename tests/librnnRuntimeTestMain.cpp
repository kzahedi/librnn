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
 * aunsigned long with librnn in the file COPYING; if not, write to the Free       *
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA     *
 * 02110-1301, USA.                                                       *
 *                                                                        *
 **************************************************************************/



#include <librnn/librnn.h>
#include <iostream>
#include <sys/time.h>
#ifndef WIN32
#include <sys/resource.h>
#endif
#include <time.h>
#include <vector>

#include <timing.hpp>

//  get the size of implementation capacity()*sizoef(element)+sizeof(vector)

using namespace std;
using namespace librnn;

#ifdef USE_LOG4CPP_OUTPUT
static unsigned long testInitLogger()
{
  cout << "Logger initialisation:" << endl;
  startTiming();
  initLogger();
  unsigned long time = stopTiming();
  printTime(time);
  return time;
}
#endif

static unsigned long testConstructor()
{
  cout << "RecurrentNeuralNetwork constructor:\t\t";
  startTiming();
#ifdef USE_MATRIX
  RNN_MATRIX(rnn);
#endif
#ifdef USE_VECTOR
  RNN_VECTOR(rnn);
#endif
  unsigned long time = stopTiming();
  printTime(time);
  delete rnn;
  return time;
}

static unsigned long testDestructor()
{
  cout << "RecurrentNeuralNetwork destructor:\t\t";
#ifdef USE_MATRIX
  RNN_MATRIX(rnn);
#endif
#ifdef USE_VECTOR
  RNN_VECTOR(rnn);
#endif
  startTiming();
  delete rnn;
  unsigned long time = stopTiming();
  printTime(time);
  return time;
}

#ifdef TIME_CONSUMING_TEST
static unsigned long testAddNeurons()
{
  cout << "RecurrentNeuralNetwork addNeuron:\t\t\t";
#ifdef USE_MATRIX
  RNN_MATRIX(rnn);
#endif
#ifdef USE_VECTOR
  RNN_VECTOR(rnn);
#endif
  startTiming();
  for(int i=0;i < 1000; i++)
  {
    rnn->createNeuron();
  }
  unsigned long time = stopTiming();
  printTime(time);
  delete rnn;
  return time;
}
#endif // TIME_CONSUMING

#ifdef TIME_CONSUMING_TEST
static unsigned long testAddSynapses()
{
  cout << "RecurrentNeuralNetwork addSynapses:\t\t";
#ifdef USE_MATRIX
  RNN_MATRIX(rnn);
#endif
#ifdef USE_VECTOR
  RNN_VECTOR(rnn);
#endif
  startTiming();
  for(int i=0;i < 1000; i++)
  {
    Neuron *n = rnn->createNeuron();
    for(int j=0;j < 1000; j++)
    {
      Synapse *s = new Synapse();
      rnn->createSynapse(n,n,0);
    }
  }
  unsigned long time = stopTiming();
  printTime(time);
  delete rnn;
  return time;
}
#endif // TIME_CONSUMING

#ifdef TIME_CONSUMING_TEST
void testLog4cppTimeConsumption()
{
  cout << "testLog4cppTimeConsumption:\t\t\t\t\t\t";
  startTiming();
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.setPriority(log4cpp::Priority::FATAL);
#endif // USE_LOG4CPP_OUTPUT

#ifdef USE_MATRIX
  RNN_MATRIX(rnn);
#endif
#ifdef USE_VECTOR
  RNN_VECTOR(rnn);
#endif
  Neuron  *inputNeuron = rnn->createNeuron();
  Neuron  *outputNeuron = rnn->createNeuron();
  Synapse *woi = rnn->createSynapse(inputNeuron,  outputNeuron,  2.0);
  Synapse *woo = rnn->createSynapse(outputNeuron, outputNeuron, -2.5);

  inputNeuron->setTransferfunction(&transferfunction_id);
  outputNeuron->setTransferfunction(&transferfunction_tanh);

  __REAL output = 0;
  __REAL bias   = -1;
  __REAL delta  = 2.0 / 1000.0;

  // mini bifurcation diagram test
  for(int i=0; i < 1000; i++)
  {
    inputNeuron->setBias(bias);
    rnn->updateActivation(inputNeuron);
    rnn->updateOutput(inputNeuron);
    for(int j=0; j < 1000; j++)
    {
      rnn->update();
      output = transferfunction_tanh( -2.5 * output + 2.0 * bias);
#ifdef USE_LOG4CPP_OUTPUT
      libRnnLogger.debug("rnn->update: %f vs. %f", outputNeuron->getOutput(), output);
#endif // USE_LOG4CPP_OUTPUT
    }
    bias += delta;
  }

  unsigned long time = stopTiming();
  printTime(time);

  delete rnn;
}
#endif // TIME_CONSUMING

#ifdef TIME_CONSUMING_TEST
void testCopy()
{
#ifdef USE_MATRIX
  RNN_MATRIX(rnnOrig);
  RNN_VECTOR(rnnCopy);
#endif
#ifdef USE_VECTOR
  RNN_MATRIX(rnnOrig);
  RNN_VECTOR(rnnCopy);
#endif
  for(int i = 0; i < 1000; i++)
  {
    Neuron *n = rnnOrig->createNeuron();
    if(drand48() < 0.5)
    {
      n->setTransferfunction(transferfunction_tanh);
    }
    else
    {
      n->setTransferfunction(transferfunction_id);
    }
  }
  for(int j = 0; j < 999; j++) // connect every neuron to neuron 0
  {
    __REAL w = ((drand48() < 0.5)?-1:1) * (10 * drand48() + 0.1);
    rnnOrig->createSynapse(rnnOrig->getNeuron(j), rnnOrig->getNeuron(j+1), w);
  }
  for(int j = 0; j < 10000; j++) // random synapses
  {
    __REAL w = ((drand48() < 0.5)?-1:1) * (10 * drand48() + 0.1);
    int source = (int)(drand48() * 100 + 0.5);
    int destination = (int)(drand48() * 100 + 0.5);
    // TODO: check why this is required for the test not to fail
    while(source != destination - 1)
    {
      source = (int)(drand48() * 100 + 0.5);
      destination = (int)(drand48() * 100 + 0.5);
    }
    rnnOrig->createSynapse(rnnOrig->getNeuron(source),
        rnnOrig->getNeuron(destination),
        w);
  }
  startTiming();
  rnnCopy->copy(rnnOrig);
  unsigned long time = stopTiming();
  cout << "RecurrentNeuralNetwork copy:\t\t\t\t\t";
  printTime(time);
  delete rnnOrig;
  delete rnnCopy;
}
#endif

int main()
{
  cout << "starting librnn runtime test." << endl;
#ifdef TIME_CONSUMING_TEST
  testAddNeurons();
#endif // TIME_CONSUMING
#ifdef USE_LOG4CPP_OUTPUT
  testInitLogger();
#endif
  testConstructor();
  testDestructor();
#ifdef TIME_CONSUMING_TEST
  testAddSynapses();
  testLog4cppTimeConsumption();
  testCopy();
#endif // TIME_CONSUMING
  cout << "done." << endl;
}
