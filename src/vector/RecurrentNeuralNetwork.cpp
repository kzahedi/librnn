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


using namespace std;
using namespace librnn;



/*! 
 * \brief Constructor
 *
 * The constructor of the class. Currently no initialisation functionality is
 * required.
 *
 */
RecurrentNeuralNetwork::RecurrentNeuralNetwork()
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.debug("constructor called");
#endif
}



/*! 
 * \brief Destructor
 *
 * The destructor of the class. Currently no de-initialisation functionality is
 * required.
 *
 */
RecurrentNeuralNetwork::~RecurrentNeuralNetwork()
{
}



/*! 
 * \brief Returns the number of neurons in the network.
 *
 * This function returns the number of neurons, which are accessible and
 * processed by this instance of a recurrent neural network.
 *
 * \return non-negative integer referring to the number of neurons in the
 * network
 *
 */
int RecurrentNeuralNetwork::getNeuronCount()
{
  return _neurons.size();
}



/*! 
 * \brief Adds a neuron to the network.
 *
 * This function adds one previously defined neuron to this instance of a
 * recurrent neural network. Only neurons that are added to the recurrent neural
 * network, will be processed by the update function. Synapses which connect
 * neurons may only be added to the network after the neurons were added. If the
 * source is compiled with design by contract, the function check for uniqueness
 * of the neuron before adding.
 *
 * \param Neuron neuron 
 *
 */
void RecurrentNeuralNetwork::add(Neuron *neuron)
{
  _neurons.push_back(neuron);
}




/*! 
 * \brief Deletes a neuron from the network.
 *
 * This function deletes a neuron from this instance of a
 * recurrent neural network. Every synapse that is connected to this neuron will
 * be deleted with it, such that there are no synapses with dead ends, which
 * could cause software exceptions.
 *
 * \param Neuron neuron 
 *
 */
void RecurrentNeuralNetwork::remove(Neuron *neuron)
{
  __vSYNAPSE list;
  __vSYNAPSE_ITERATOR i;

  __FOR(_neuronIterator, _neurons)
  {
    //list = (*_neuronIterator)->cleanUpConnectionsTo(neuron);
    Neuron *n = (*_neuronIterator);
    n->cleanUpConnectionsTo(neuron);
  }

  __FOR(_synapseIterator, _synapses)
  {
    if( (*_synapseIterator)->status() == __SYNAPSE_STATUS_DEAD)
    {
#ifdef USE_LOG4CPP_OUTPUT
      libRnnLogger.debug("RecurrentNeuralNetwork::remove(Neuron): remove synapse with source %d and destination %d", 
          (*_synapseIterator)->source()->getId(), (*_synapseIterator)->destination()->getId());
#endif
      _synapses.erase(_synapseIterator);
      delete (*_synapseIterator);
      _synapseIterator--;
    }
  }

  __REMOVE_ELEMENT_FROM_VECTOR(_neurons, neuron, _neuronIterator)
  delete neuron;
}



/*! 
 * \brief Adds a synapse to the neural network
 *
 * A synapse must be fully defined before it is added to the neural network.
 * The neurons, which are connected by the synapses must be part of the network
 * before the synapse is added.
 *
 * \param Synapse synapse 
 * \return boolean if the synapse was added or not
 *
 */
void RecurrentNeuralNetwork::add(Synapse *synapse)
{
  Neuron *source      = synapse->source();
  Neuron *destination = synapse->destination();

  _synapses.push_back(synapse);

  if(source == destination)
  {
    source->add(synapse);
  }
  else
  {
    source->add(synapse);
    destination->add(synapse);
  }
}



void RecurrentNeuralNetwork::remove(Synapse *synapse)
{
  Neuron *source      = synapse->source();
  Neuron *destination = synapse->destination();

  source->remove(synapse);
  destination->remove(synapse);

  __REMOVE_ELEMENT_FROM_VECTOR(_synapses,synapse,_synapseIterator)
}



int RecurrentNeuralNetwork::getSynapsesCount()
{
  return _synapses.size();
}



int RecurrentNeuralNetwork::countSynapses()
{
  int numberOfSynapses = 0;

  __FOR(_neuronIterator, _neurons)
  {
    numberOfSynapses += (*_neuronIterator)->getSynapsesCount();
  }
  return numberOfSynapses;
}



void RecurrentNeuralNetwork::update()
{
  __FOR(_neuronIterator, _neurons)
  {
    (*_neuronIterator)->updateActivation();
  }

  __FOR(_neuronIterator, _neurons)
  {
    (*_neuronIterator)->updateOutput();
  }
}


void RecurrentNeuralNetwork::add(Neuron *neuron, Synapse *synapse)
{
  neuron->add(synapse);
}

void RecurrentNeuralNetwork::updateActivation(Neuron *neuron)
{
  neuron->updateActivation();
}

void RecurrentNeuralNetwork::updateOutput(Neuron *neuron)
{
  neuron->updateOutput();
}

int RecurrentNeuralNetwork::getSynapsesCount(Neuron *neuron)
{
  return neuron->getSynapsesCount();
}

int RecurrentNeuralNetwork::getAdjacentSynapsesCount(Neuron *neuron)
{
  return neuron->getAdjacentSynapsesCount();
}

int RecurrentNeuralNetwork::getIncidentSynapsesCount(Neuron *neuron)
{
  return neuron->getIncidentSynapsesCount();
}


Synapse*  RecurrentNeuralNetwork::getSynapse(Neuron *neuron, int index)
{
  return neuron->getSynapse(index);
}

__REAL RecurrentNeuralNetwork::getActivation(Neuron *neuron)
{
  return neuron->getActivation();
}

__REAL RecurrentNeuralNetwork::getOutput(Neuron *neuron)
{
  return neuron->getOutput();
}

Neuron* RecurrentNeuralNetwork::getNeuron(int index)
{
  return _neurons[index];
}

