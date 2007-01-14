#ifndef __SYNAPSE_H__
#define __SYNAPSE_H__

#include <librnn/globals.h>
#include <librnn/AbstractNeuron.h>
#include <librnn/AbstractSynapse.h>

namespace librnn
{
  class Synapse: public AbstractSynapse
  {
    public:
      Synapse();
      ~Synapse();

      dReal strength();

    private:
      AbstractNeuron *_source;
      AbstractNeuron *_destination;
      double _weight;
  };
}

#endif // __SYNAPSE_H__
