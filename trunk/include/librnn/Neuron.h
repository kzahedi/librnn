#ifndef __NEURON_H__
#define __NEURON_H__

#include <librnn/globals.h>
#include <librnn/AbstractNeuron.h>
#include <librnn/AbstractSynapse.h>

namespace librnn
{
  class Neuron: public AbstractNeuron
  {
    public:
      Neuron();
      ~Neuron();
      void update();

      void addIncidentSynapse(AbstractSynapse *newSynapse);
      void addAdjacentSynapse(AbstractSynapse *newSynapse);

    private:
      dReal activation;
      dReal output;

#ifdef IMPL_ADJ_LIST
      slist<AbstractSynapse*> _incident;
      slist<AbstractSynapse*> _adjacent;
      slist<AbstractSynapse*> _synapses;
#endif

#ifdef IMPL_ADJ_VECTOR
      slist<AbstractSynapse*> _incident;
      slist<AbstractSynapse*> _adjacent;
      slist<AbstractSynapse*> _synapses;
#endif
  };
}

#endif // __NEURON_H__
