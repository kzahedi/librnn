// first naive implementation to get a feeling for RNN
// to test between list and vector implementation
#include <librnn/RecurrentNeuralNetwork.h>

#include <utility>                   // for std::pair
#include <algorithm>                 // for std::for_each
#include <boost/graph/dijkstra_shortest_paths.hpp>


using namespace std;
using namespace librnn;

RecurrentNeuralNetwork::RecurrentNeuralNetwork()
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.debug("constructor called");
#endif
#ifdef IMPL_ADJ_LIST
  _numberOfNeurons = 0;
#endif
  _numberOfSynapses = 0;
}

RecurrentNeuralNetwork::~RecurrentNeuralNetwork()
{
}


int RecurrentNeuralNetwork::getNumberOfNeurons()
{
#ifdef IMPL_ADJ_LIST
  return _numberOfNeurons;
#endif
#ifdef IMPL_ADJ_VECTOR
  return _neurons.size();
#endif
}

void RecurrentNeuralNetwork::addNeuron(Neuron *newNeuron)
{
#ifdef IMPL_ADJ_VECTOR
  _neurons.push_back(newNeuron);
#endif
#ifdef IMPL_ADJ_LIST
  _neurons.push_front(newNeuron);
  ++_numberOfNeurons;
#endif
}

void RecurrentNeuralNetwork::addSynapse(Synapse *newSynapse)
{
  _numberOfSynapses++;
  if(newSynapse->source() == newSynapse->destination())
  {
    newSynapse->source()->addSynapse(newSynapse);
  }
  else
  {
    newSynapse->destination()->addSynapse(newSynapse);
  }
}

int RecurrentNeuralNetwork::getSynapsesCount()
{
  return _numberOfSynapses;
}

int RecurrentNeuralNetwork::countSynapses()
{
  _numberOfSynapses = 0;

  for(_neuronIterator = _neurons.begin(); 
      _neuronIterator != _neurons.end();
      _neuronIterator++)
  {
    cout << "_numberOfSynapses: " << _numberOfSynapses << endl;
    _numberOfSynapses += (*_neuronIterator)->getSynapsesCount();
    cout << "_numberOfSynapses: " << _numberOfSynapses << endl;
  }
  return _numberOfSynapses;
}
