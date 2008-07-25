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
__RecurrentNeuralNetwork_MatrixImplementation::__RecurrentNeuralNetwork_MatrixImplementation()
{
  _numberOfNeurons = 0;
  _numberOfSynapses = 0;
  _neurons = new Neuron*[0];
  _synapses = new Synapse*[0];
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
__RecurrentNeuralNetwork_MatrixImplementation::~__RecurrentNeuralNetwork_MatrixImplementation()
{
  __cleanUp();
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
int __RecurrentNeuralNetwork_MatrixImplementation::getNeuronCount()
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
void __RecurrentNeuralNetwork_MatrixImplementation::__add(Neuron *neuron)
{
  Neuron **tmpNeuronArray = new Neuron*[_numberOfNeurons];
  // copy all neurons to temporary array
  for(int i=0; i < _numberOfNeurons; i++)
  {
    tmpNeuronArray[i] = _neurons[i];
    //delete _neurons[i];
  }
  delete[] _neurons;
  // create new, larger array
  _neurons = new Neuron*[_numberOfNeurons+1];
  // copy all neurons back
  for(int i=0; i < _numberOfNeurons; i++)
  {
    _neurons[i] = tmpNeuronArray[i];
  }
  // add new neuron to array
  _neurons[_numberOfNeurons] = neuron; 

  // create temporary synapse array
  Synapse **tmpSynapseArray = new Synapse*[ _numberOfNeurons * _numberOfNeurons];

  for(int i=0; i < _numberOfNeurons * _numberOfNeurons; i++)
  {
    tmpSynapseArray[i] = _synapses[i];
    //delete _synapses[i];
  }
  delete _synapses;

  _numberOfNeurons++;

  // now recreate synapse matrix
  _synapses = new Synapse*[_numberOfNeurons * _numberOfNeurons];

  for(int i = 0; i < _numberOfNeurons - 1; i++)
  {
    for(int j = 0; j < _numberOfNeurons - 1; j++)
    {
      _synapses[__synapseIndex(i, j)] =
        tmpSynapseArray[i + ((_numberOfNeurons - 1)* j)];
    }
  }

  for(int i=0; i < _numberOfNeurons; i++)
  {
    // last column
    _synapses[(_numberOfNeurons - 1) + i * _numberOfNeurons] = new Synapse(NULL, NULL, 0); 
   _synapses[(_numberOfNeurons - 1) + i * _numberOfNeurons]->setStatus(__SYNAPSE_STATUS_DEAD);
    // last row
    _synapses[i + (_numberOfNeurons - 1) * _numberOfNeurons] = new Synapse(NULL, NULL, 0); 
     _synapses[i + (_numberOfNeurons - 1) * _numberOfNeurons]->setStatus(__SYNAPSE_STATUS_DEAD);
  }



  delete[] tmpSynapseArray;

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
void __RecurrentNeuralNetwork_MatrixImplementation::remove(Neuron *neuron)
{
  int index = __getNeuronIndex(neuron);

  if(index == -1)
  {
#ifdef USE_LOG4CPP_OUTPUT
    libRnnLogger.fatal("removed unknown neuron with index %d", neuron->getId());
#endif // USE_LOG4CPP_OUTPUT
    __cleanUpAndExit();
  }

  for(int i = 0; i < _numberOfNeurons; i++)
  {
    if(_synapses[__synapseIndex(i,index)]->status() 
        == __SYNAPSE_STATUS_VALID)
    {
      _numberOfSynapses--;
      _synapses[__synapseIndex(i,index)]->setStatus(__SYNAPSE_STATUS_DEAD);
    }
    if(_synapses[__synapseIndex(index,i)]->status() 
        == __SYNAPSE_STATUS_VALID)
    {
      _numberOfSynapses--;
      _synapses[__synapseIndex(index,i)]->setStatus(__SYNAPSE_STATUS_DEAD);
    }
  }

  Synapse **tmpSynapseArray = new Synapse*[ _numberOfNeurons * _numberOfNeurons];

  for(int i=0; i < _numberOfNeurons * _numberOfNeurons; i++)
  {
    tmpSynapseArray[i] = _synapses[i];
    //delete _synapses[i];
  }
  delete _synapses;


  Neuron **tmpNeuronArray = new Neuron*[_numberOfNeurons-1];
  int tmpIndex = -1;
  int copyIndex = -1;
  for(int i=0; i < _numberOfNeurons; i++)
  {
    copyIndex++;
    if(i == index)
    {
      continue;
    }
    tmpIndex++;
    tmpNeuronArray[tmpIndex] = _neurons[copyIndex];
  }
  delete[] _neurons;
  _neurons = new Neuron*[_numberOfNeurons-1];
  for(int i=0; i < _numberOfNeurons-1; i++)
  {
    _neurons[i] = tmpNeuronArray[i];
  }

  _numberOfNeurons--;

  _synapses = new Synapse*[_numberOfNeurons * _numberOfNeurons];

  int oldIndex = 0;
  for(int i = 0; i < _numberOfNeurons; i++)
  {
    for(int j = 0; j < _numberOfNeurons; j++)
    {
      oldIndex = i + ((i > index - 1)?1:0) + j * (_numberOfNeurons + 1) + ((j>index-1)?_numberOfNeurons + 1:0);
      _synapses[__synapseIndex(i, j)] = tmpSynapseArray[oldIndex];
    }
  }

  delete tmpSynapseArray;
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
void __RecurrentNeuralNetwork_MatrixImplementation::__add(Synapse *synapse)
{
  int sourceIndex = __getSourceIndex(synapse);
  int destinationIndex = __getDestinationIndex(synapse);
  if(sourceIndex == -1 || destinationIndex == -1)
  {
#ifdef USE_LOG4CPP_OUTPUT
    libRnnLogger.fatal("add - unknown source or destination");
#endif // USE_LOG4CPP_OUTPUT
    __cleanUpAndExit();
  }

  if(_synapses[__synapseIndex(sourceIndex, destinationIndex)] == NULL)
  {
  }

  if(_synapses[__synapseIndex(sourceIndex, destinationIndex)]->status()
      == __SYNAPSE_STATUS_DEAD)
  {
    _numberOfSynapses++;
  }
  _synapses[__synapseIndex(sourceIndex, destinationIndex)] = synapse;
}



void __RecurrentNeuralNetwork_MatrixImplementation::remove(Synapse *synapse)
{
  if(synapse->status() != __SYNAPSE_STATUS_DEAD && __found(synapse))
  {
    synapse->setStatus(__SYNAPSE_STATUS_DEAD);
    _numberOfSynapses--;
  }
}



int __RecurrentNeuralNetwork_MatrixImplementation::getSynapsesCount()
{
  return _numberOfSynapses; // all which are != 0
}



int __RecurrentNeuralNetwork_MatrixImplementation::countSynapses()
{
  int count = 0;
  for(int j = 0; j < _numberOfNeurons; j++)
  {
    for(int i = 0; i < _numberOfNeurons; i++)
    {
      if(_synapses[__synapseIndex(i,j)]->status() == __SYNAPSE_STATUS_VALID)
      {
        count++;
      }
      if(i != j && _synapses[__synapseIndex(j,i)]->status() == __SYNAPSE_STATUS_VALID)
      {
        count++;
      }
    }
  }
  return count;
}



void __RecurrentNeuralNetwork_MatrixImplementation::update()
{
  for(int i = 0; i < _numberOfNeurons; i++)
  {
    updateActivation(_neurons[i]);
  }
  for(int i = 0; i < _numberOfNeurons; i++)
  {
    updateOutput(_neurons[i]);
  }
}




void __RecurrentNeuralNetwork_MatrixImplementation::updateActivation(Neuron *neuron)
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.fatal("updateActivation - not implement yet");
#endif // USE_LOG4CPP_OUTPUT
  __REAL activation = neuron->getBias();
  int index = __getNeuronIndex(neuron);
  for(int i = 0; i < _numberOfNeurons; i++)
  {
    activation += 
      _synapses[__synapseIndex(i,index)]->strength() 
      * _neurons[i]->getOutput();
  }
  neuron->setActivation(activation);
}

void __RecurrentNeuralNetwork_MatrixImplementation::updateOutput(Neuron *neuron)
{
  neuron->setOutput(neuron->transfer(neuron->getActivation()));
}

int __RecurrentNeuralNetwork_MatrixImplementation::getSynapsesCount(Neuron *neuron)
{
  int count = 0;
  int index = __getNeuronIndex(neuron);
  if(index == -1)
  {
#ifdef USE_LOG4CPP_OUTPUT
    libRnnLogger.fatal("unknown neuron");
#endif // USE_LOG4CPP_OUTPUT
    exit(-1);
  }
  for(int i = 0; i < _numberOfNeurons; i++)
  {
    if(_synapses[__synapseIndex(i,index)]->status() == 
        __SYNAPSE_STATUS_VALID)
    {
      count++;
    }
    if(i != index && _synapses[__synapseIndex(index,i)]->status() ==
        __SYNAPSE_STATUS_VALID)
    {
      count++;
    }
  }
  return count;
}


int __RecurrentNeuralNetwork_MatrixImplementation::getAdjacentSynapsesCount(Neuron *neuron)
{
  int count = 0;
  int index = __getNeuronIndex(neuron);
  if(index == -1)
  {
#ifdef USE_LOG4CPP_OUTPUT
    libRnnLogger.fatal("unknown neuron");
#endif // USE_LOG4CPP_OUTPUT
    exit(-1);
  }

  for(int i = 0; i < _numberOfNeurons; i++)
  {
    if(_synapses[__synapseIndex(index,i)]->status() 
        == __SYNAPSE_STATUS_VALID)
    {
      count++;
    }
  }
  return count;

}

int __RecurrentNeuralNetwork_MatrixImplementation::getIncidentSynapsesCount(Neuron *neuron)
{
  int count = 0;
  int index = __getNeuronIndex(neuron);
  if(index == -1)
  {
#ifdef USE_LOG4CPP_OUTPUT
    libRnnLogger.fatal("unknown neuron");
#endif // USE_LOG4CPP_OUTPUT
    exit(-1);
  }

  for(int i = 0; i < _numberOfNeurons; i++)
  {
    if(_synapses[__synapseIndex(i,index)]->status() 
        == __SYNAPSE_STATUS_VALID)
    {
      count++;
    }
  }
  return count;
}


Synapse*  __RecurrentNeuralNetwork_MatrixImplementation::getSynapse(Neuron *neuron, int index)
{
  int dindex = __getNeuronIndex(neuron);
  return _synapses[__synapseIndex(dindex,index)];
}

__REAL __RecurrentNeuralNetwork_MatrixImplementation::getActivation(Neuron *neuron)
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.fatal("getActivation - not implement yet");
#endif // USE_LOG4CPP_OUTPUT
  return -1;
}

__REAL __RecurrentNeuralNetwork_MatrixImplementation::getOutput(Neuron *neuron)
{
  return neuron->getOutput();
}

void __RecurrentNeuralNetwork_MatrixImplementation::__cleanUp()
{
  delete[] _neurons;
  delete[] _synapses;
}

void __RecurrentNeuralNetwork_MatrixImplementation::__cleanUpAndExit()
{
  exit(-1);
}

Neuron* __RecurrentNeuralNetwork_MatrixImplementation::getNeuron(int index)
{
  return (_neurons[index]);
}

int __RecurrentNeuralNetwork_MatrixImplementation::__getNeuronIndex(Neuron *neuron)
{
  for(int i = 0; i < _numberOfNeurons; i++)
  {
    if(neuron == _neurons[i])
    {
      return i;
    }
  }
  return -1;
}

int __RecurrentNeuralNetwork_MatrixImplementation::__getSourceIndex(Synapse *synapse)
{
  return __getNeuronIndex(synapse->source());
}

int __RecurrentNeuralNetwork_MatrixImplementation::__getDestinationIndex(Synapse *synapse)
{
  return __getNeuronIndex(synapse->destination());
}

int __RecurrentNeuralNetwork_MatrixImplementation::__synapseIndex(int x, int y)
{
  return x + _numberOfNeurons * y;
}

bool __RecurrentNeuralNetwork_MatrixImplementation::__found(Synapse *s)
{
  for(int i = 0; i < _numberOfNeurons * _numberOfNeurons; i++)
  {
    if(_synapses[i] == s) return true;
  }
  return false;
}

Neuron* __RecurrentNeuralNetwork_MatrixImplementation::createNeuron()
{
  // TODO: needs refactoring
  __add(new Neuron());
  return getNeuron(_numberOfNeurons-1);
}

Synapse* __RecurrentNeuralNetwork_MatrixImplementation::createSynapse(Neuron *source, Neuron *destination, __REAL strength)
{
  // TODO: needs refactoring
  __add(new Synapse(source, destination, strength));
  return _synapses[__synapseIndex(__getNeuronIndex(source), __getNeuronIndex(destination))];
}


