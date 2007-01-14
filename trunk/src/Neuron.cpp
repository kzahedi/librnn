#include <librnn/Neuron.h>

using namespace librnn;

Neuron::Neuron()
{

}

Neuron::~Neuron()
{

}

void Neuron::update()
{

}

void Neuron::addIncidentSynapse(AbstractSynapse *newSynapse)
{
#ifdef IMPL_ADJ_VECTOR
  _incident.push_back(newSynapse);
  _synapses.push_back(newSynapse);
#endif
#ifdef IMPL_ADJ_LIST
  _incident.push_front(newSynapse);
  _synapses.push_front(newSynapse);
#endif
}


void Neuron::addAdjacentSynapse(AbstractSynapse *newSynapse)
{
#ifdef IMPL_ADJ_VECTOR
  _adjacent.push_back(newSynapse);
  _synapses.push_back(newSynapse);
#endif
#ifdef IMPL_ADJ_LIST
  _adjacent.push_front(newSynapse);
  _synapses.push_front(newSynapse);
#endif
  
}
