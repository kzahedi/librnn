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

#include <librnn/Neuron.h>
#include <librnn/Synapse.h>
#include <librnn/librnn.h>

using namespace librnn;

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


  class RecurrentNeuralNetwork 
  {
    public:
      RecurrentNeuralNetwork();
      ~RecurrentNeuralNetwork();

      int getNumberOfNeurons();

      void addNeuron(Neuron *neuron);
      void addSynapse(Synapse *synapse);
      int  getSynapsesCount();
      int  countSynapses();

      void update();

    private:
      int _numberOfSynapses;

#ifdef IMPL_ADJ_LIST
      slist<Neuron*> _neurons;
      slist<Neuron*>::iterator _neuronIterator;
      int _numberOfNeurons;
#endif

#ifdef IMPL_ADJ_VECTOR
      vector<Neuron*> _neurons;
      vector<Neuron*>::iterator _neuronIterator;
#endif



  };
}
#endif  //__RNN_H__
