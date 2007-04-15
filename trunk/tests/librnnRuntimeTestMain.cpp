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



#include <librnn/librnn.h>
#include <iostream>
#include <sys/time.h>
#include <sys/resource.h>
#include <time.h>
#include <vector>

#include <timing.hpp>

//  get the size of implementation capacity()*sizoef(element)+sizeof(vector)

using namespace std;
using namespace librnn;

#ifdef USE_LOG4CPP_OUTPUT
static long testInitLogger()
{
  cout << "Logger initialisation:" << endl;
  startTiming();
  initLogger();
  long time = stopTiming();
  printTime(time);
  return time;
}
#endif

static long testConstructor()
{
  cout << "RecurrentNeuralNetwork constructor:\t\t";
  startTiming();
  RecurrentNeuralNetwork *rnn = new RecurrentNeuralNetwork();
  long time = stopTiming();
  printTime(time);
  delete rnn;
  return time;
}

static long testDestructor()
{
  cout << "RecurrentNeuralNetwork destructor:\t\t";
  RecurrentNeuralNetwork *rnn = new RecurrentNeuralNetwork();
  startTiming();
  delete rnn;
  long time = stopTiming();
  printTime(time);
  return time;
}

static long testAddNeurons()
{
  cout << "RecurrentNeuralNetwork addNeuron (1M adds):\t";
  RecurrentNeuralNetwork *rnn = new RecurrentNeuralNetwork();
  startTiming();
  for(int i=0;i < 1000000; i++)
  {
    Neuron *n = new Neuron();
    rnn->addNeuron(n);
  }
  long time = stopTiming();
  printTime(time);
  delete rnn;
  return time;
}

static long testAddSynapses()
{
  cout << "RecurrentNeuralNetwork addSynapses (1M adds):\t";
  RecurrentNeuralNetwork *rnn = new RecurrentNeuralNetwork();
  startTiming();
  for(int i=0;i < 1000; i++)
  {
    Neuron *n = new Neuron();
    for(int j=0;j < 1000; j++)
    {
      Synapse *s = new Synapse();
      n->addSynapse(s);
    }
    rnn->addNeuron(n);
  }
  long time = stopTiming();
  printTime(time);
  delete rnn;
  return time;
}



int main()
{
  cout << "starting librnn runtime test." << endl;
  testAddNeurons();
#ifdef USE_LOG4CPP_OUTPUT
  testInitLogger();
#endif
  testConstructor();
  testDestructor();
  testAddSynapses();
}
