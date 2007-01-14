#ifndef __ABSTRACT_SYNAPSE_H__
#define __ABSTRACT_SYNAPSE_H__

namespace librnn 
{
  class AbstractSynapse 
  {
    public:
      virtual dReal strength() = 0;
    
  };
}

#endif // __ABSTRACT_SYNAPSE_H__
