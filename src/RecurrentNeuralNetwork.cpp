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



// first naive implementation to get a feeling for RNN
// to test between list and vector implementation
#include <librnn/RecurrentNeuralNetwork.h>

#include <utility>                   // for std::pair
#include <algorithm>                 // for std::for_each
#include <boost/graph/dijkstra_shortest_paths.hpp>


using namespace std;
using namespace librnn;

RecurrentNeuralNetwork::RecurrentNeuralNetwork()
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.debug("constructor called");
#endif

#ifdef IMPL_ADJ_LIST
  _numberOfNeurons = 0;
#endif

  _numberOfSynapses = 0;
}

RecurrentNeuralNetwork::~RecurrentNeuralNetwork()
{
}


int RecurrentNeuralNetwork::getNumberOfNeurons()
{
#ifdef IMPL_ADJ_LIST
  return _numberOfNeurons;
#endif
#ifdef IMPL_ADJ_VECTOR
  return _neurons.size();
#endif
}

void RecurrentNeuralNetwork::addNeuron(Neuron *newNeuron)
{
#ifdef IMPL_ADJ_VECTOR
  _neurons.push_back(newNeuron);
#endif
#ifdef IMPL_ADJ_LIST
  _neurons.push_front(newNeuron);
  ++_numberOfNeurons;
#endif
}

void RecurrentNeuralNetwork::addSynapse(Synapse *newSynapse)
{
  _numberOfSynapses++;

  Neuron *source      = newSynapse->source();
  Neuron *destination = newSynapse->destination();

  if(source == destination)
  {
    source->addSynapse(newSynapse);
  }
  else
  {
    source->addSynapse(newSynapse);
    destination->addSynapse(newSynapse);
  }

}

int RecurrentNeuralNetwork::getSynapsesCount()
{
  return _numberOfSynapses;
}

int RecurrentNeuralNetwork::countSynapses()
{
  _numberOfSynapses = 0;

  for(_neuronIterator = _neurons.begin(); 
      _neuronIterator != _neurons.end();
      _neuronIterator++)
  {
    _numberOfSynapses += (*_neuronIterator)->getSynapsesCount();
  }
  return _numberOfSynapses;
}

void RecurrentNeuralNetwork::update()
{
  for(_neuronIterator = _neurons.begin(); 
      _neuronIterator != _neurons.end();
      _neuronIterator++)
  {
    (*_neuronIterator)->updateActivation();
  }
  for(_neuronIterator = _neurons.begin(); 
      _neuronIterator != _neurons.end();
      _neuronIterator++)
  {
    (*_neuronIterator)->updateOutput();
  }

}
