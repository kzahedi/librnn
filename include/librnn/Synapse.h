#ifndef __SYNAPSE_H__
#define __SYNAPSE_H__

#include <librnn/AbstractSynapse.h>

namespace librnn
{
  class Synapse: public AbstractSynapse
  {
    public:
      Synapse();
      ~Synapse();

      Synapse(AbstractNeuron *source, AbstractNeuron *destination);
      Synapse(AbstractNeuron *source, AbstractNeuron *destination, REAL strength);

      AbstractNeuron* source();
      AbstractNeuron* destination();

      REAL strength();

    private:
      void init();

      AbstractNeuron *_source;
      AbstractNeuron *_destination;

      double _strength;
  };
}

#endif // __SYNAPSE_H__
