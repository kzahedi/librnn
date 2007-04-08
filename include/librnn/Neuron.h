#ifndef __NEURON_H__
#define __NEURON_H__

#include <librnn/globals.h>
#include <librnn/AbstractNeuron.h>
#include <librnn/AbstractSynapse.h>

#include <string>
#include <iostream>

using namespace std;

namespace librnn
{

  class NeuronException : public std::exception
  {
    public:
      explicit NeuronException(const std::string& what)
        :
          m_what(what)
    {}

      virtual ~NeuronException() throw() {}

      virtual const char * what() const throw()
      {
        return m_what.c_str();
      }

      virtual void message() const throw()
      {
        cerr << "NeuronException: " << m_what << endl;
      }


    private:
      std::string m_what;
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

      int  getSynapsesCount();

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
      int _numberOfSynapses;
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
