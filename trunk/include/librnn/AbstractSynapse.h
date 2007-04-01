#ifndef __ABSTRACT_SYNAPSE_H__
#define __ABSTRACT_SYNAPSE_H__

#include <librnn/defines.h>
#include <librnn/AbstractNeuron.h>

namespace librnn 
{


  class AbstractSynapse 
  {
    public:
      virtual REAL strength() = 0;

      virtual AbstractNeuron* source() = 0;
      virtual AbstractNeuron* destination() = 0;
    
  };
}

#endif // __ABSTRACT_SYNAPSE_H__
