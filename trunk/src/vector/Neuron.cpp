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

#include <iostream>



using namespace librnn;



__Neuron_VectorImplementation::__Neuron_VectorImplementation()
{
  _transferfunction = NULL;
  _bias       = 0;
  _activation = 0;
  _output     = 0;
}



__Neuron_VectorImplementation::~__Neuron_VectorImplementation()
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.debug("This neuron is deleted");
#endif
}



void __Neuron_VectorImplementation::updateActivation()
{
  _activation = _bias;
  int i=0;
  double w = 0.0;
  double o = 0.0;
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.debug("__Neuron_VectorImplementation::updateActivation activation before loop = %f",
      _activation);
#endif
  for(_synapseIterator = _incident.begin();
      _synapseIterator != _incident.end(); _synapseIterator++)
  {
    w = (*_synapseIterator)->strength();
    o = (((*_synapseIterator)->source())->getOutput());
    _activation += w * o;
#ifdef USE_LOG4CPP_OUTPUT
    libRnnLogger.debug(
        "__Neuron_VectorImplementation::updateActivation activation in loop = %f ( += %f * %f)",
        _activation, w, o);
#endif
  }
}



void __Neuron_VectorImplementation::updateOutput() throw(NeuronException)
{
  if(_transferfunction == NULL)
  {
    throw NeuronException("no transfer function specified");
  }
  _output = _transferfunction(_activation);
}



void __Neuron_VectorImplementation::setTransferfunction(Transferfunction transferfunction)
{
  _transferfunction = transferfunction;
}



__REAL __Neuron_VectorImplementation::getOutput()
{
  return _output;
}



__REAL __Neuron_VectorImplementation::getActivation()
{
  return _activation;
}



void __Neuron_VectorImplementation::setActivation(__REAL activation)
{
  _activation = activation;
}



void __Neuron_VectorImplementation::add(Synapse *synapse)
{
  _synapses.push_back(synapse);

  if(synapse->source() == (Neuron*)this)
  {
    __addAdjacentSynapse(synapse);
  }

  if(synapse->destination() == (Neuron*)this)
  {
    __addIncidentSynapse(synapse);
  }
}



void __Neuron_VectorImplementation::remove(Synapse *synapse)
{

  __REMOVE_ELEMENT_FROM_VECTOR(_synapses, synapse, _synapseIterator)

  if(synapse->source() == (Neuron*)this)
  {
    __delAdjacentSynapse(synapse);
  }

  if(synapse->destination() == (Neuron*)this)
  {
    __delIncidentSynapse(synapse);
  }
}



void __Neuron_VectorImplementation::__delIncidentSynapse(Synapse *synapse)
{

  __REMOVE_ELEMENT_FROM_VECTOR(_incident, synapse, _synapseIterator);

}



void __Neuron_VectorImplementation::__addIncidentSynapse(Synapse *synapse)
{
  _incident.push_back(synapse);
}



void __Neuron_VectorImplementation::__delAdjacentSynapse(Synapse *synapse)
{
  __REMOVE_ELEMENT_FROM_VECTOR(_adjacent, synapse, _synapseIterator);
}



void __Neuron_VectorImplementation::__addAdjacentSynapse(Synapse *synapse)
{
  _adjacent.push_back(synapse);
}



int __Neuron_VectorImplementation::getSynapsesCount()
{
  return _synapses.size();
}



int __Neuron_VectorImplementation::getIncidentSynapsesCount()
{
  return _incident.size();
}



int __Neuron_VectorImplementation::getAdjacentSynapsesCount()
{
  return _adjacent.size();
}



Synapse* __Neuron_VectorImplementation::getSynapse(int index)
{
  return _synapses[index];
}



void __Neuron_VectorImplementation::setBias(__REAL bias)
{
  _bias = bias;
}



__REAL __Neuron_VectorImplementation::getBias()
{
  return _bias;
}


void __Neuron_VectorImplementation::cleanUpConnectionsTo(Neuron *neuron)
{
  cleanUpConnectionsTo((__Neuron_VectorImplementation*)neuron);
}

void __Neuron_VectorImplementation::cleanUpConnectionsTo(__Neuron_VectorImplementation *neuron)
{
#ifdef USE_LOG4CPP_OUTPUT
      libRnnLogger.debug("__Neuron_VectorImplementation::cleanUpConnectionsTo: START %d\n_synapses.size() = %d", _id, _synapses.size());
#endif
  bool inList = false;

  __FOR(_synapseIterator, _synapses)
  {
#ifdef USE_LOG4CPP_OUTPUT
      libRnnLogger.debug("checking synapse with source %d and destination %d and status %d",
          (*_synapseIterator)->source()->getId(), (*_synapseIterator)->destination()->getId(),
          (*_synapseIterator)->status());
#endif
    if( (*_synapseIterator)->source() == (Neuron*)neuron ||
        (*_synapseIterator)->destination() == (Neuron*)neuron)
    {
      (*_synapseIterator)->setStatus(__SYNAPSE_STATUS_DEAD);
#ifdef USE_LOG4CPP_OUTPUT
      libRnnLogger.debug("setting synapse with source %d and destination %d dead %d",
          (*_synapseIterator)->source()->getId(), (*_synapseIterator)->destination()->getId(),
          (*_synapseIterator)->status());
#endif
    }
  }



#ifdef USE_LOG4CPP_OUTPUT
      libRnnLogger.debug("erasing from _synapses list");
#endif
  __FOR(_synapseIterator, _synapses)
  {
#ifdef USE_LOG4CPP_OUTPUT
      libRnnLogger.debug("checking if synapse with source %d and destination %d is dead",
          (*_synapseIterator)->source()->getId(), (*_synapseIterator)->destination()->getId());
      if((*_synapseIterator)->status() == __SYNAPSE_STATUS_DEAD)
      {
        libRnnLogger.debug("true");
      }
      else
      {
        libRnnLogger.debug("false");
      }
#endif
    if( (*_synapseIterator)->status() == __SYNAPSE_STATUS_DEAD)
    {
#ifdef USE_LOG4CPP_OUTPUT
      libRnnLogger.debug("removing synapse with source %d and destination %d from _synapses",
          (*_synapseIterator)->source()->getId(), (*_synapseIterator)->destination()->getId());
#endif
      _synapses.erase(_synapseIterator);
      _synapseIterator--;
    }
  }


#ifdef USE_LOG4CPP_OUTPUT
      libRnnLogger.debug("erasing from _incident list");
#endif
  __FOR(_synapseIterator, _incident)
  {
#ifdef USE_LOG4CPP_OUTPUT
      libRnnLogger.debug("checking if synapse with source %d and destination %d is dead",
          (*_synapseIterator)->source()->getId(), (*_synapseIterator)->destination()->getId());
      if((*_synapseIterator)->status() == __SYNAPSE_STATUS_DEAD)
      {
        libRnnLogger.debug("true");
      }
      else
      {
        libRnnLogger.debug("false");
      }
#endif
    if( (*_synapseIterator)->status() == __SYNAPSE_STATUS_DEAD)
    {
#ifdef USE_LOG4CPP_OUTPUT
      libRnnLogger.debug("removing synapse with source %d and destination %d from _incident",
          (*_synapseIterator)->source()->getId(), (*_synapseIterator)->destination()->getId());
#endif
      _incident.erase(_synapseIterator);
      _synapseIterator--;
    }
  }

#ifdef USE_LOG4CPP_OUTPUT
      libRnnLogger.debug("erasing from _adjacent list");
#endif
  __FOR(_synapseIterator, _adjacent)
  {
#ifdef USE_LOG4CPP_OUTPUT
      libRnnLogger.debug("checking if synapse with source %d and destination %d is dead",
          (*_synapseIterator)->source()->getId(), (*_synapseIterator)->destination()->getId());
      if((*_synapseIterator)->status() == __SYNAPSE_STATUS_DEAD)
      {
        libRnnLogger.debug("true");
      }
      else
      {
        libRnnLogger.debug("false");
      }
#endif
    if( (*_synapseIterator)->status() == __SYNAPSE_STATUS_DEAD)
    {
#ifdef USE_LOG4CPP_OUTPUT
      libRnnLogger.debug("removing synapse with source %d and destination %d from _adjacent",
          (*_synapseIterator)->source()->getId(), (*_synapseIterator)->destination()->getId());
#endif
      _adjacent.erase(_synapseIterator);
      _synapseIterator--;
    }
  }


#ifdef USE_LOG4CPP_OUTPUT
      libRnnLogger.debug("__Neuron_VectorImplementation::cleanUpConnectionsTo: END");
#endif
}



int __Neuron_VectorImplementation::getId()
{
  return _id;
}

void __Neuron_VectorImplementation::setOutput(__REAL output)
{
  _output = output;
}

__REAL __Neuron_VectorImplementation::transfer(__REAL x) throw(NeuronException)
{
  return 0; // TODO: needs refactoring
}



