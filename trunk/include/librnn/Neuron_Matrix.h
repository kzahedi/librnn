#ifndef __NEURON_MATRIX_H__
#define __NEURON_MATRIX_H__

#include <librnn/librnn.h>

using namespace std;

namespace librnn
{
  class __Neuron_MatrixImplementation : public Neuron
  {
    public:
      __Neuron_MatrixImplementation();
      ~__Neuron_MatrixImplementation();

      void updateActivation();
      void updateOutput() throw(librnn::NeuronException);

      void setTransferfunction(Transferfunction transferfunction);
      Transferfunction getTransferfunction();
      __REAL transfer(__REAL x) throw(librnn::NeuronException);

      void setActivation(__REAL activation);

      __REAL getActivation();

      __REAL getOutput();
      void setOutput(__REAL output);

      void setBias(__REAL bias);
      __REAL getBias();

      int getId();

      void copy(Neuron *source);

    private:
      int _id;

      __REAL _activation;
      __REAL _bias;
      __REAL _output;

      Transferfunction _transferfunction;
  };
}
#endif // __NEURON_MATRIX_H__
