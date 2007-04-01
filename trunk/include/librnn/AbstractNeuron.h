#ifndef __ABSTRACT_NEURON_H__
#define __ABSTRACT_NEURON_H__

#include <librnn/defines.h>
#include <librnn/AbstractSynapse.h>

#include <string>

namespace librnn 
{
  class AbstractNeuron 
  {
    public:
      virtual void updateOutput() = 0;
      virtual void updateActivation() = 0;
      virtual void addSynapse(AbstractSynapse *s) = 0;
      virtual REAL getOutput() = 0;
    
  };

}

#endif // __ABSTRACT_NEURON_H__
