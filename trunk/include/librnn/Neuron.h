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

      void setActivation(REAL activation);

      int  getSynapsesCount();
      int  getAdjacentSynapsesCount();
      int  getIncidentSynapsesCount();

      REAL getActivation();
      REAL getOutput();

      void setBias(REAL bias);
      REAL getBias();


      Synapse* getSynapse(int index);

    private:
      void addIncidentSynapse(Synapse *synapse);
      void addAdjacentSynapse(Synapse *synapse);
      void delIncidentSynapse(Synapse *synapse);
      void delAdjacentSynapse(Synapse *synapse);

      REAL _activation;
      REAL _bias;
      REAL _output;

      Transferfunction _transferfunction;

#ifdef IMPL_ADJ_LIST
      slist<Synapse*> _incident;
      slist<Synapse*> _adjacent;
      slist<Synapse*> _synapses;

      slist<Synapse*>::iterator _incidentIterator;
      int _numberOfSynapses;
      int _numberOfAdjacentSynapses;
      int _numberOfIncidentSynapses;
#endif

#ifdef IMPL_ADJ_VECTOR
      vector<Synapse*> _incident;
      vector<Synapse*> _adjacent;
      vector<Synapse*> _synapses;

      vector<Synapse*>::iterator _synapseIterator;
#endif
  };
}

#endif // __NEURON_H__
