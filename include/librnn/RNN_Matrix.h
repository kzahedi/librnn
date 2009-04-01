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



#ifndef __RNN_MATRIX_H__
#define __RNN_MATRIX_H__

#include <librnn/librnn.h>

#include <string>
#include <iostream>

#define RNN_MATRIX(a) \
  a = new __RecurrentNeuralNetwork_MatrixImplementation();

using namespace librnn;
using namespace std;

namespace librnn
{

  /*! 
   * \class RecurrentNeuralNetwork - Matrix implementation
   *
   * \brief Implementation of a Recurrent Neural Network, using vectors to 
   *         store neurons and synapses.
   *
   * This class implements a recurrent neural network as vector of pointers to
   * neurons and synapses. Both are stored in stl::vector containers. Functions
   * are provided to alter the structure, access information of
   * the current status, and process the neural network.
   */
  class __RecurrentNeuralNetwork_MatrixImplementation : public RecurrentNeuralNetwork
  {
    public:
      __RecurrentNeuralNetwork_MatrixImplementation();
      ~__RecurrentNeuralNetwork_MatrixImplementation();

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

      Synapse*  getSynapse(Neuron *source, Neuron *destination);
      Synapse*  getSynapse(int sourceIndex, int destinationIndex);
      Neuron*   getNeuron(int index);

      void update();

      void copy(RecurrentNeuralNetwork *source);

    protected:
      void __cleanUp();

    private:
      void __add(Neuron *neuron);
      void __add(Synapse *synapse);

      void __cleanUpAndExit();
      int __getNeuronIndex(Neuron *neuron);
      int __getSourceIndex(Synapse *synapse);
      int __getDestinationIndex(Synapse *synapse);
      bool __found(Synapse *s);
      int __synapseIndex(int x, int y);
      // TODO for matrix only
      int _numberOfNeurons;
      int _numberOfSynapses;
      Neuron              **_neurons;
      Synapse             **_synapses;
  };
}
#endif  //__RNN_MATRIX_H__
