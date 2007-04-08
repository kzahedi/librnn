#ifndef __RNN_H__
#define __RNN_H__

#include <librnn/globals.h>
#include <librnn/Neuron.h>
#include <librnn/Synapse.h>


using namespace std;

namespace librnn
{
  class RecurrentNeuralNetworkException : public std::exception
  {
    public:
      explicit RecurrentNeuralNetworkException(const std::string& what)
        :
          m_what(what)
    {}

      virtual ~RecurrentNeuralNetworkException() throw() {}

      virtual const char * what() const throw()
      {
        return m_what.c_str();
      }

      virtual void message() const throw()
      {
        cerr << "RecurrentNeuralNetworkException: " << m_what << endl;
      }

    private:
      std::string m_what;
  };


  class RecurrentNeuralNetwork 
  {
    public:
      RecurrentNeuralNetwork();
      ~RecurrentNeuralNetwork();

      int getNumberOfNeurons();

      void addNeuron(Neuron *neuron);
      void addSynapse(Synapse *synapse);
      int  getSynapsesCount();
      int  countSynapses();

    private:
      int _numberOfSynapses;

#ifdef IMPL_ADJ_LIST
      slist<Neuron*> _neurons;
      slist<Neuron*>::iterator _neuronIterator;
      int _numberOfNeurons;
#endif

#ifdef IMPL_ADJ_VECTOR
      vector<Neuron*> _neurons;
      vector<Neuron*>::iterator _neuronIterator;
#endif



  };
}
#endif  //__RNN_H__
