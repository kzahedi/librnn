#ifndef __NEURON_H__
#define __NEURON_H__

#include <librnn/globals.h>
#include <librnn/AbstractNeuron.h>
#include <librnn/AbstractSynapse.h>

#include <string>

using namespace std;

namespace librnn
{
  class NeuronException
  {
    public:
      NeuronException(string message)
      {
        _message = message;
      };

      string message()
      {
        return _message;
      };
    private:
      string _message;
  };

  class Neuron: public AbstractNeuron
  {
    public:
      Neuron();
      ~Neuron();

      void updateActivation();
      void updateOutput() throw(librnn::NeuronException);

      void setTransferfunction(Transferfunction transferfunction);

      void addSynapse(AbstractSynapse *newSynapse);

      void setActivation(REAL activation);

      REAL getActivation();
      REAL getOutput();

    private:
      void addIncidentSynapse(AbstractSynapse *newSynapse);
      void addAdjacentSynapse(AbstractSynapse *newSynapse);

      REAL _activation;
      REAL _bias;
      REAL _output;
      Transferfunction _transferfunction;

#ifdef IMPL_ADJ_LIST
      slist<AbstractSynapse*> _incident;
      slist<AbstractSynapse*> _adjacent;
      slist<AbstractSynapse*> _synapses;

      slist<AbstractSynapse*>::iterator _incidentIterator;
#endif

#ifdef IMPL_ADJ_VECTOR
      vector<AbstractSynapse*> _incident;
      vector<AbstractSynapse*> _adjacent;
      vector<AbstractSynapse*> _synapses;

      vector<AbstractSynapse*>::iterator _incidentIterator;
#endif
  };

}

#endif // __NEURON_H__
