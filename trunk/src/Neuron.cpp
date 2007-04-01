#include <iostream>
#include <librnn/Neuron.h>

using namespace librnn;

Neuron::Neuron()
{
  _transferfunction = NULL;
}

Neuron::~Neuron()
{

}

void Neuron::updateActivation()
{
  _activation = _bias;
  for(_incidentIterator = _incident.begin();
      _incidentIterator != _incident.end(); _incidentIterator++)
  {
    _activation += (*_incidentIterator)->strength() * ((*_incidentIterator)->source())->getOutput();
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
  return _output;
}


void Neuron::setActivation(REAL activation)
{
  _activation = activation;
}

void Neuron::addSynapse(AbstractSynapse *newSynapse)
{
#ifdef IMPL_ADJ_VECTOR
  _synapses.push_back(newSynapse);
#endif
#ifdef IMPL_ADJ_LIST
  _synapses.push_front(newSynapse);
#endif

  if(newSynapse->source() == this)
  {
    addAdjacentSynapse(newSynapse);
  }

  if(newSynapse->source() == this)
  {
    addIncidentSynapse(newSynapse);
  }
}

void Neuron::addIncidentSynapse(AbstractSynapse *newSynapse)
{
#ifdef IMPL_ADJ_VECTOR
  _incident.push_back(newSynapse);
#endif
#ifdef IMPL_ADJ_LIST
  _incident.push_front(newSynapse);
#endif
}


void Neuron::addAdjacentSynapse(AbstractSynapse *newSynapse)
{
#ifdef IMPL_ADJ_VECTOR
  _adjacent.push_back(newSynapse);
#endif
#ifdef IMPL_ADJ_LIST
  _adjacent.push_front(newSynapse);
#endif
  
}




