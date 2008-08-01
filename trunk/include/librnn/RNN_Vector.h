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



#ifndef __RNN_VECTOR_H__
#define __RNN_VECTOR_H__

#include <librnn/librnn.h>

#include <string>
#include <iostream>

#define RNN_VECTOR(a) \
  __RecurrentNeuralNetwork_VectorImplementation *a = \
  new __RecurrentNeuralNetwork_VectorImplementation();

using namespace librnn;
using namespace std;

namespace librnn
{

  /*! 
   * \class RecurrentNeuralNetwork - Vector Implementation
   *
   * \brief Implementation of a Recurrent Neural Network, using vectors to 
   *         store neurons and synapses.
   *
   * This class implements a recurrent neural network as vector of pointers to
   * neurons and synapses. Both are stored in stl::vector containers. Functions
   * are provided to alter the structure, access information of
   * the current status, and process the neural network.
   */
  class __RecurrentNeuralNetwork_VectorImplementation : public RecurrentNeuralNetwork
  {
    public:
      __RecurrentNeuralNetwork_VectorImplementation();
      ~__RecurrentNeuralNetwork_VectorImplementation();

     int getNeuronCount();

     void remove(Neuron *neuron);
     void remove(Synapse *synapse);

     void updateActivation(Neuron *neuron);
     void updateOutput(Neuron *neuron);

     __REAL getActivation(Neuron *neuron);
     __REAL getOutput(Neuron *neuron);


     int  getSynapsesCount();
     int  countSynapses();

     int  getSynapsesCount(Neuron *neuron);
     int  getAdjacentSynapsesCount(Neuron *neuron);
     int  getIncidentSynapsesCount(Neuron *neuron);

     Neuron* createNeuron();
     void createNeurons(int numberOfNewNeurons);
     Synapse* createSynapse(Neuron* source, Neuron* destination, __REAL strength);

     Synapse* getSynapse(int sourceIndex, int destinationIndex);
     Synapse* getSynapse(Neuron *source, Neuron *destination);
     Neuron*  getNeuron(int index);

     void update();

     void copy(RecurrentNeuralNetwork *source);

    protected:
      void __cleanUp();

    private:
     void __add(Neuron *neuron);
     void __add(Synapse *synapse);

      /// vector of neurons in the network
      __vNEURON_VECTOR           _neurons;
      /// iterator for the neurons vector
      __vNEURON_VECTOR_ITERATOR  _neuronIterator;

      /// vector of synapses in the network
      __vSYNAPSE                 _synapses;
      /// iterator for the synapses vector
      __vSYNAPSE_ITERATOR        _synapseIterator;
  };
}
#endif  //__RNN_VECTOR_H__
