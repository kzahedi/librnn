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

// matrix implementation

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
  _numberOfNeurons = 0;
  _numberOfSynapses = 0;
  _neurons = new Neuron[0];
  _synapses = new Synapse[0];
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.debug("matrix implementation - constructor called");
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
  return _numberOfNeurons;
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
  Neuron *tmpNeuronArray = new Neuron[_numberOfNeurons];
  for(int i=0; i < _numberOfNeurons; i++)
  {
    tmpNeuronArray[i] = _neurons[i];
  }
  delete[] _neurons;
  _neurons = new Neuron[_numberOfNeurons+1];
  for(int i=0; i < _numberOfNeurons; i++)
  {
    _neurons[i] = tmpNeuronArray[i];
  }
  _neurons[_numberOfNeurons] = *neuron;
  _numberOfNeurons++;
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
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.fatal("remove - not implement yet");
#endif // USE_LOG4CPP_OUTPUT
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
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.fatal("add - not implement yet");
#endif // USE_LOG4CPP_OUTPUT

}



void RecurrentNeuralNetwork::remove(Synapse *synapse)
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.fatal("remove - not implement yet");
#endif // USE_LOG4CPP_OUTPUT
}



int RecurrentNeuralNetwork::getSynapsesCount()
{
  return _numberOfSynapses; // all which are != 0
}



int RecurrentNeuralNetwork::countSynapses()
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.fatal("countSynapses - not implement yet");
#endif // USE_LOG4CPP_OUTPUT
}



void RecurrentNeuralNetwork::update()
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.fatal("update - not implement yet");
#endif // USE_LOG4CPP_OUTPUT
}



void RecurrentNeuralNetwork::add(Neuron *neuron, Synapse *synapse)
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.fatal("add - not implement yet");
#endif // USE_LOG4CPP_OUTPUT

}

void RecurrentNeuralNetwork::updateActivation(Neuron *neuron)
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.fatal("updateActivation - not implement yet");
#endif // USE_LOG4CPP_OUTPUT
}

void RecurrentNeuralNetwork::updateOutput(Neuron *neuron)
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.fatal("updateOutput - not implement yet");
#endif // USE_LOG4CPP_OUTPUT
}

int RecurrentNeuralNetwork::getSynapsesCount(Neuron *neuron)
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.fatal("getSynapsesCount - not implement yet");
#endif // USE_LOG4CPP_OUTPUT
  return -1;
}


int RecurrentNeuralNetwork::getAdjacentSynapsesCount(Neuron *neuron)
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.fatal("getAdjacentSynapsesCount - not implement yet");
#endif // USE_LOG4CPP_OUTPUT
  return -1;
}

int RecurrentNeuralNetwork::getIncidentSynapsesCount(Neuron *neuron)
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.fatal("getIncidentSynapsesCount - not implement yet");
#endif // USE_LOG4CPP_OUTPUT
  return -1;
}


Synapse*  RecurrentNeuralNetwork::getSynapse(Neuron *neuron, int index)
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.fatal("getSynapse - not implement yet");
#endif // USE_LOG4CPP_OUTPUT
  return NULL;
}

__REAL RecurrentNeuralNetwork::getActivation(Neuron *neuron)
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.fatal("getActivation - not implement yet");
#endif // USE_LOG4CPP_OUTPUT
  return -1;
}

__REAL RecurrentNeuralNetwork::getOutput(Neuron *neuron)
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.fatal("getOutput - not implement yet");
#endif // USE_LOG4CPP_OUTPUT
  return -1;
}
