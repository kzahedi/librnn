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



#ifndef __RNN_H__
#define __RNN_H__

#include <librnn/librnn.h>

#include <string>
#include <iostream>

using namespace librnn;
using namespace std;

namespace librnn
{
  class RecurrentNeuralNetworkException : public std::exception
  {
    public:
      explicit RecurrentNeuralNetworkException(const std::string& what)
        :
          m_what(what)
      {}

      virtual ~RecurrentNeuralNetworkException() throw() {}

      virtual const char * what() const throw()
      {
        return m_what.c_str();
      }

      virtual void message() const throw()
      {
        cerr << "RecurrentNeuralNetworkException: " << m_what << endl;
      }


    private:
      std::string m_what;
  };


  /*! 
   * \class RecurrentNeuralNetwork
   *
   * \brief Implementation of a Recurrent Neural Network, using vectors to 
   *         store neurons and synapses.
   *
   * This class implements a recurrent neural network as vector of pointers to
   * neurons and synapses. Both are stored in stl::vector containers. Functions
   * are provided to alter the structure, access information of
   * the current status, and process the neural network.
   */
  class RecurrentNeuralNetwork 
  {
    public:

      virtual int getNeuronCount() = 0;

      virtual void remove(Neuron *neuron) = 0 ;
      virtual void remove(Synapse *synapse) = 0 ;

      virtual void updateActivation(Neuron *neuron) = 0;
      virtual void updateOutput(Neuron *neuron) = 0 ;
      
      virtual __REAL getActivation(Neuron *neuron) = 0;
      virtual __REAL getOutput(Neuron *neuron) = 0;


      virtual int  getSynapsesCount() = 0;
      virtual int  countSynapses() = 0;

      virtual int  getSynapsesCount(Neuron *neuron) = 0;
      virtual int  getAdjacentSynapsesCount(Neuron *neuron) = 0;
      virtual int  getIncidentSynapsesCount(Neuron *neuron) = 0;

      virtual Neuron* createNeuron() = 0;
      virtual Synapse* createSynapse(Neuron* source, Neuron* destination, __REAL strength) = 0;

      virtual Synapse*  getSynapse(Neuron *neuron, int index) = 0;
      virtual Neuron*   getNeuron(int index) = 0;

      virtual void update() = 0;
      
    private:
      virtual void __add(Neuron *neuron) = 0;
      virtual void __add(Synapse *synapse) = 0;
  };
}
#endif  //__RNN_H__
