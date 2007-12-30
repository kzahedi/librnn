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



#ifndef __NEURON_H__
#define __NEURON_H__

#include <librnn/librnn.h>

#include <string>
#include <iostream>

using namespace std;

namespace librnn
{
  class NeuronException : public std::exception
  {
    public:
      explicit NeuronException(const std::string& what)
        :
          m_what(what)
      {}

      virtual ~NeuronException() throw() {}

      virtual const char * what() const throw()
      {
        return m_what.c_str();
      }

      virtual void message() const throw()
      {
        cerr << "NeuronException: " << m_what << endl;
      }


    private:
      std::string m_what;
  };

#ifdef USE_VECTOR
  class Neuron
  {
    public:
      Neuron();
      ~Neuron();

      void updateActivation();
      void updateOutput() throw(librnn::NeuronException);

      void setTransferfunction(Transferfunction transferfunction);

      void add(Synapse *synapse);
      void remove(Synapse *synapse);
      Synapse* getSynapse(int index);

      void setActivation(__REAL activation);

      int  getSynapsesCount();
      int  getAdjacentSynapsesCount();
      int  getIncidentSynapsesCount();

      __REAL getActivation();
      __REAL getOutput();

      void setBias(__REAL bias);
      __REAL getBias();

      void cleanUpConnectionsTo(Neuron *neuron);

      int getId();


    private:
      void addIncidentSynapse(Synapse *synapse);
      void addAdjacentSynapse(Synapse *synapse);
      void delIncidentSynapse(Synapse *synapse);
      void delAdjacentSynapse(Synapse *synapse);

      int _id;

      __REAL _activation;
      __REAL _bias;
      __REAL _output;

      Transferfunction _transferfunction;

      __vSYNAPSE _incident;
      __vSYNAPSE _adjacent;
      __vSYNAPSE _synapses;

      __vSYNAPSE::iterator _synapseIterator;
  };
#endif // USE_VECTOR
#ifdef USE_MATRIX
  class Neuron
  {
    public:
      Neuron();
      ~Neuron();

      void updateActivation();
      void updateOutput() throw(librnn::NeuronException);

      void setTransferfunction(Transferfunction transferfunction);
      __REAL transfer(__REAL x) throw(librnn::NeuronException);

      void setActivation(__REAL activation);

      __REAL getActivation();

      __REAL getOutput();
      void setOutput(__REAL output);

      void setBias(__REAL bias);
      __REAL getBias();

      int getId();

      void copy(Neuron *neuron);

    private:
      int _id;

      __REAL _activation;
      __REAL _bias;
      __REAL _output;

      Transferfunction _transferfunction;
  };
#endif // USE_MATRIX
}
#endif // __NEURON_H__
