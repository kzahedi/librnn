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



#include <librnn/Neuron.h>

#include <iostream>

using namespace librnn;

Neuron::Neuron()
{
  _transferfunction = NULL;
#ifdef IMPL_ADJ_LIST
  _numberOfSynapses = 0;
  _numberOfAdjacentSynapses = 0;
  _numberOfIncidentSynapses = 0;
#endif

  _bias       = 0;
  _activation = 0;
  _output     = 0;
}

Neuron::~Neuron()
{

}

void Neuron::updateActivation()
{
  _activation = _bias;
  int i=0;
  double w = 0.0;
  double o = 0.0;
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.debug("Neuron::updateActivation activation before loop = %f", _activation);
#endif
  for(_incidentIterator = _incident.begin();
      _incidentIterator != _incident.end(); _incidentIterator++)
  {
    w = (*_incidentIterator)->strength();
    o = (((*_incidentIterator)->source())->getOutput());
    _activation += w * o;
#ifdef USE_LOG4CPP_OUTPUT
    libRnnLogger.debug("Neuron::updateActivation activation in loop = %f ( += %f * %f)", _activation, w, o);
#endif
  }
}


void Neuron::updateOutput() throw(NeuronException)
{
  if(_transferfunction == NULL)
  {
    throw NeuronException("no transfer function specified");
  }
  _output = _transferfunction(_activation);
}

void Neuron::setTransferfunction(Transferfunction transferfunction)
{
  _transferfunction = transferfunction;
}

REAL Neuron::getOutput()
{
  return _output;
}

REAL Neuron::getActivation()
{
  return _activation;
}


void Neuron::setActivation(REAL activation)
{
  _activation = activation;
}

void Neuron::addSynapse(Synapse *newSynapse)
{
#ifdef IMPL_ADJ_VECTOR
  _synapses.push_back(newSynapse);
#endif
#ifdef IMPL_ADJ_LIST
  _synapses.push_front(newSynapse);
  _numberOfSynapses++;
#endif

  if(newSynapse->source() == this)
  {
    addAdjacentSynapse(newSynapse);
  }

  if(newSynapse->destination() == this)
  {
    addIncidentSynapse(newSynapse);
  }
}

void Neuron::addIncidentSynapse(Synapse *newSynapse)
{
#ifdef IMPL_ADJ_VECTOR
  _incident.push_back(newSynapse);
#endif
#ifdef IMPL_ADJ_LIST
  _incident.push_front(newSynapse);
  _numberOfIncidentSynapses++;
#endif
}


void Neuron::addAdjacentSynapse(Synapse *newSynapse)
{
#ifdef IMPL_ADJ_VECTOR
  _adjacent.push_back(newSynapse);
#endif
#ifdef IMPL_ADJ_LIST
  _adjacent.push_front(newSynapse);
  _numberOfAdjacentSynapses++;
#endif
  
}

int Neuron::getSynapsesCount()
{
#ifdef IMPL_ADJ_LIST
  return _numberOfSynapses;
#endif
#ifdef IMPL_ADJ_VECTOR
  return _synapses.size();
#endif
}


int Neuron::getIncidentSynapsesCount()
{
#ifdef IMPL_ADJ_LIST
  return _numberOfIncidentSynapses;
#endif
#ifdef IMPL_ADJ_VECTOR
  return _incident.size();
#endif
}


int Neuron::getAdjacentSynapsesCount()
{
#ifdef IMPL_ADJ_LIST
  return _numberOfAdjacentSynapses;
#endif
#ifdef IMPL_ADJ_VECTOR
  return _adjacent.size();
#endif
}

Synapse* Neuron::getSynapse(int index)
{
  return _synapses[index];
}

void Neuron::setBias(REAL bias)
{
  _bias = bias;
}

REAL Neuron::getBias()
{
  return _bias;
}
