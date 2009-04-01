#ifndef __NEURON_VECTOR_H__
#define __NEURON_VECTOR_H__

#include <librnn/librnn.h>

using namespace std;

namespace librnn
{
  class __Neuron_VectorImplementation : public Neuron
  {
    public:
      __Neuron_VectorImplementation();
      ~__Neuron_VectorImplementation();

      void updateActivation();
      void updateOutput() throw(librnn::NeuronException);

      void setTransferfunction(Transferfunction transferfunction);
      Transferfunction getTransferfunction();
      __REAL transfer(__REAL x) throw(librnn::NeuronException); // TODO: need refactoring
      
      void setActivation(__REAL activation);

      __REAL getActivation();

      __REAL getOutput();
      void setOutput(__REAL output);

      void setBias(__REAL bias);
      __REAL getBias();

      int getId();

      void cleanUpConnectionsTo(__Neuron_VectorImplementation *neuron);
      void cleanUpConnectionsTo(Neuron *neuron);

      void copy(Neuron *source);

      void add(Synapse *synapse);
      void remove(Synapse *synapse);
      Synapse* getSynapse(int index);

      int  getSynapsesCount();
      int  getAdjacentSynapsesCount();
      int  getIncidentSynapsesCount();

      Synapse* getAdjacentSynapse(Neuron *destination);
      Synapse* getIncidentSynapse(Neuron *source);

    private:
      void __addIncidentSynapse(Synapse *synapse);
      void __addAdjacentSynapse(Synapse *synapse);
      void __delIncidentSynapse(Synapse *synapse);
      void __delAdjacentSynapse(Synapse *synapse);

      int _id;

      __REAL _activation;
      __REAL _bias;
      __REAL _output;

      Transferfunction _transferfunction;

      __vSYNAPSE _incident;
      __vSYNAPSE _adjacent;
      __vSYNAPSE _synapses;

      __vSYNAPSE::iterator _synapseIterator;
  };
}
#endif // ___NEURON_VECTOR_H__
