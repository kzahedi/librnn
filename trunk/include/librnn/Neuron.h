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

  class Neuron
  {
    public:
      Neuron();
      ~Neuron();

      void updateActivation();
      void updateOutput() throw(librnn::NeuronException);

      void setTransferfunction(Transferfunction transferfunction);

      void addSynapse(Synapse *synapse);
      void delSynapse(Synapse *synapse);
      Synapse* getSynapse(int index);

      void setActivation(REAL activation);

      int  getSynapsesCount();
      int  getAdjacentSynapsesCount();
      int  getIncidentSynapsesCount();

      REAL getActivation();
      REAL getOutput();

      void setBias(REAL bias);
      REAL getBias();

      vSYNAPSE cleanUpConnectionsTo(Neuron *neuron);

    private:
      void addIncidentSynapse(Synapse *synapse);
      void addAdjacentSynapse(Synapse *synapse);
      void delIncidentSynapse(Synapse *synapse);
      void delAdjacentSynapse(Synapse *synapse);

      REAL _activation;
      REAL _bias;
      REAL _output;

      Transferfunction _transferfunction;

      vSYNAPSE _incident;
      vSYNAPSE _adjacent;
      vSYNAPSE _synapses;

      vSYNAPSE::iterator _synapseIterator;
  };
}

#endif // __NEURON_H__
