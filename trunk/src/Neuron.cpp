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
 * FITNESS __FOR A PARTICULAR PURPOSE.                                      *
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
  _bias       = 0;
  _activation = 0;
  _output     = 0;
  _id = numberOfNeurons;
  numberOfNeurons++;
}



Neuron::~Neuron()
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.debug("This neuron is deleted");
#endif
}



void Neuron::updateActivation()
{
  _activation = _bias;
  int i=0;
  double w = 0.0;
  double o = 0.0;
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.debug("Neuron::updateActivation activation before loop = %f",
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
        "Neuron::updateActivation activation in loop = %f ( += %f * %f)",
        _activation, w, o);
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



__REAL Neuron::getOutput()
{
  return _output;
}



__REAL Neuron::getActivation()
{
  return _activation;
}



void Neuron::setActivation(__REAL activation)
{
  _activation = activation;
}



void Neuron::add(Synapse *synapse)
{
  _synapses.push_back(synapse);

  if(synapse->source() == this)
  {
    addAdjacentSynapse(synapse);
  }

  if(synapse->destination() == this)
  {
    addIncidentSynapse(synapse);
  }
}



void Neuron::remove(Synapse *synapse)
{

  __REMOVE_ELEMENT_FROM_VECTOR(_synapses, synapse, _synapseIterator)

  if(synapse->source() == this)
  {
    delAdjacentSynapse(synapse);
  }

  if(synapse->destination() == this)
  {
    delIncidentSynapse(synapse);
  }
}



void Neuron::delIncidentSynapse(Synapse *synapse)
{

  __REMOVE_ELEMENT_FROM_VECTOR(_incident, synapse, _synapseIterator);

}



void Neuron::addIncidentSynapse(Synapse *synapse)
{
  _incident.push_back(synapse);
}



void Neuron::delAdjacentSynapse(Synapse *synapse)
{
  __REMOVE_ELEMENT_FROM_VECTOR(_adjacent, synapse, _synapseIterator);
}



void Neuron::addAdjacentSynapse(Synapse *synapse)
{
  _adjacent.push_back(synapse);
}



int Neuron::getSynapsesCount()
{
  return _synapses.size();
}



int Neuron::getIncidentSynapsesCount()
{
  return _incident.size();
}



int Neuron::getAdjacentSynapsesCount()
{
  return _adjacent.size();
}



Synapse* Neuron::getSynapse(int index)
{
  return _synapses[index];
}



void Neuron::setBias(__REAL bias)
{
  _bias = bias;
}



__REAL Neuron::getBias()
{
  return _bias;
}



void Neuron::cleanUpConnectionsTo(Neuron *neuron)
{
#ifdef USE_LOG4CPP_OUTPUT
      libRnnLogger.debug("Neuron::cleanUpConnectionsTo: START %d\n_synapses.size() = %d", _id, _synapses.size());
#endif
  bool inList = false;

  __FOR(_synapseIterator, _synapses)
  {
#ifdef USE_LOG4CPP_OUTPUT
      libRnnLogger.debug("checking synapse with source %d and destination %d and status %d",
          (*_synapseIterator)->source()->getId(), (*_synapseIterator)->destination()->getId(),
          (*_synapseIterator)->status());
#endif
    if( (*_synapseIterator)->source() == neuron ||
        (*_synapseIterator)->destination() == neuron)
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
      libRnnLogger.debug("Neuron::cleanUpConnectionsTo: END");
#endif
}



int Neuron::getId()
{
  return _id;
}
