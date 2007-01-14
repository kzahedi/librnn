#ifndef __RNN_H__
#define __RNN_H__

#include <librnn/globals.h>
#include <librnn/Neuron.h>


using namespace std;

namespace librnn
{

  class RecurrentNeuralNetwork 
  {
    public:
      RecurrentNeuralNetwork();
      ~RecurrentNeuralNetwork();

      int getNumberOfNeurons();

      bool addNeuron(Neuron *neuron);

    private:

#ifdef IMPL_ADJ_LIST
      slist<Neuron*> _neurons;
      int _numberOfNeurons;
#endif

#ifdef IMPL_ADJ_VECTOR
      vector<Neuron*> _neurons;
#endif

  };
}
#endif  //__RNN_H__
