#ifndef __RNN_H__
#define __RNN_H__

namespace librnn
{
  class RecurrentNeuralNetwork 
  {
    public:
      RecurrentNeuralNetwork();
      ~RecurrentNeuralNetwork();

      void init(int numberOfNeurons, int numberOfSynapses);


      int getNumberOfSynapses();
      int getNumberOfNeurons();


    private:
      int _numberOfSynapses;
      int _numberOfNeurons;
      double *a;
  };
}
#endif  //__RNN_H__
