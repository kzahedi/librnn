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


using namespace std;
using namespace librnn;



/*! 
 * \brief Constructor
 *
 * The constructor of the class. Currently no initialisation functionality is
 * required.
 *
 */
__RecurrentNeuralNetwork_VectorImplementation::__RecurrentNeuralNetwork_VectorImplementation()
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
__RecurrentNeuralNetwork_VectorImplementation::~__RecurrentNeuralNetwork_VectorImplementation()
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
int __RecurrentNeuralNetwork_VectorImplementation::getNeuronCount()
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
void __RecurrentNeuralNetwork_VectorImplementation::__add(Neuron *neuron)
{
  _neurons.push_back((__Neuron_VectorImplementation*)neuron);
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
void __RecurrentNeuralNetwork_VectorImplementation::remove(Neuron *neuron)
{
  __vSYNAPSE list;
  __vSYNAPSE_ITERATOR i;

  __FOR(_neuronIterator, _neurons)
  {
    //list = (*_neuronIterator)->cleanUpConnectionsTo(neuron);
    __Neuron_VectorImplementation *n = (*_neuronIterator);
    n->cleanUpConnectionsTo((__Neuron_VectorImplementation*)neuron);
  }

  __FOR(_synapseIterator, _synapses)
  {
    if( (*_synapseIterator)->status() == __SYNAPSE_STATUS_DEAD)
    {
#ifdef USE_LOG4CPP_OUTPUT
      libRnnLogger.debug("__RecurrentNeuralNetwork_VectorImplementation::remove(Neuron): remove synapse with source %d and destination %d", 
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
void __RecurrentNeuralNetwork_VectorImplementation::__add(Synapse *synapse)
{
  __Neuron_VectorImplementation *source      = (__Neuron_VectorImplementation*)synapse->source();
  __Neuron_VectorImplementation *destination = (__Neuron_VectorImplementation*)synapse->destination();

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



void __RecurrentNeuralNetwork_VectorImplementation::remove(Synapse *synapse)
{
  __Neuron_VectorImplementation *source      = (__Neuron_VectorImplementation*)synapse->source();
  __Neuron_VectorImplementation *destination = (__Neuron_VectorImplementation*)synapse->destination();

  source->remove(synapse);
  destination->remove(synapse);

  __REMOVE_ELEMENT_FROM_VECTOR(_synapses,synapse,_synapseIterator)
}



int __RecurrentNeuralNetwork_VectorImplementation::getSynapsesCount()
{
  return _synapses.size();
}



int __RecurrentNeuralNetwork_VectorImplementation::countSynapses()
{
  int numberOfSynapses = 0;

  __FOR(_neuronIterator, _neurons)
  {
    numberOfSynapses += (*_neuronIterator)->getSynapsesCount();
  }
  return numberOfSynapses;
}



void __RecurrentNeuralNetwork_VectorImplementation::update()
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


void __RecurrentNeuralNetwork_VectorImplementation::updateActivation(Neuron *neuron)
{
  neuron->updateActivation();
}

void __RecurrentNeuralNetwork_VectorImplementation::updateOutput(Neuron *neuron)
{
  neuron->updateOutput();
}

int __RecurrentNeuralNetwork_VectorImplementation::getSynapsesCount(Neuron *neuron)
{
  return ((__Neuron_VectorImplementation*)neuron)->getSynapsesCount();
}

int __RecurrentNeuralNetwork_VectorImplementation::getAdjacentSynapsesCount(Neuron *neuron)
{
  return ((__Neuron_VectorImplementation*)neuron)->getAdjacentSynapsesCount();
}

int __RecurrentNeuralNetwork_VectorImplementation::getIncidentSynapsesCount(Neuron *neuron)
{
  return ((__Neuron_VectorImplementation*)neuron)->getIncidentSynapsesCount();
}


Synapse*  __RecurrentNeuralNetwork_VectorImplementation::getSynapse(Neuron *source, Neuron* destination)
{
  return ((__Neuron_VectorImplementation*)source)->getAdjacentSynapse(destination);
}

Synapse* __RecurrentNeuralNetwork_VectorImplementation::getSynapse(int sourceIndex, int destinationIndex)
{
  return NULL;
}

__REAL __RecurrentNeuralNetwork_VectorImplementation::getActivation(Neuron *neuron)
{
  return neuron->getActivation();
}

__REAL __RecurrentNeuralNetwork_VectorImplementation::getOutput(Neuron *neuron)
{
  return neuron->getOutput();
}

Neuron* __RecurrentNeuralNetwork_VectorImplementation::getNeuron(int index)
{
  return _neurons[index];
}

Neuron* __RecurrentNeuralNetwork_VectorImplementation::createNeuron()
{
  // TODO: needs refactoring
  __add(new __Neuron_VectorImplementation());
  return (Neuron*)(_neurons[_neurons.size()-1]);
}

Synapse* __RecurrentNeuralNetwork_VectorImplementation::createSynapse(Neuron *source, Neuron *destination, __REAL strength)
{
  // TODO: needs refactoring
  __add(new Synapse(source, destination, strength));
  return _synapses[_synapses.size()-1];
}

void __RecurrentNeuralNetwork_VectorImplementation::copy(RecurrentNeuralNetwork *source)
{
  this->__cleanUp();
  this->createNeurons(source->getNeuronCount());
  for(int i = 0; i < source->getNeuronCount(); i++)
  {
    for(int j = 0; j < source->getNeuronCount(); j++)
    {
      Synapse *s = source->getSynapse(i,j);
      if(s != NULL)
      {
        this->createSynapse(_neurons[i],_neurons[j], s->strength());
      }
    }
  }
}



void __RecurrentNeuralNetwork_VectorImplementation::createNeurons(int numberOfNewNeurons)
{
  // TODO: needs refactoring
  for(int i = 0; i < numberOfNewNeurons; i++)
  {
    this->createNeuron();
  }

}

void __RecurrentNeuralNetwork_VectorImplementation::__cleanUp()
{
  _neurons.clear();
  _synapses.clear();
}


