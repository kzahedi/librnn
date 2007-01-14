#ifndef __ABSTRACT_NEURON_H__
#define __ABSTRACT_NEURON_H__

#include <librnn/AbstractSynapse.h>

namespace librnn 
{
  class AbstractNeuron 
  {
    public:
      virtual void update() = 0;
      virtual void addAdjacentSynapse(AbstractSynapse *s) = 0;
      virtual void addIncidentSynapse(AbstractSynapse *s) = 0;
    
  };
}

#endif // __ABSTRACT_NEURON_H__
