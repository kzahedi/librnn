#ifndef __RNN_H__
#define __RNN_H__

#include <librnn/librnn.h>

#ifdef IMPL_ADJ_LIST
#include <ext/slist>
#endif

#ifdef IMPL_ADJ_VECTOR
#include <vector>
#endif


using namespace __gnu_cxx;

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
