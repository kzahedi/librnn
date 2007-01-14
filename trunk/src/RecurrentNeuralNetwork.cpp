#include <librnn/librnn.h>

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

bool RecurrentNeuralNetwork::addNeuron(Neuron *newNeuron)
{
#ifdef IMPL_ADJ_VECTOR
  _neurons.push_back(newNeuron);
#endif
#ifdef IMPL_ADJ_LIST
  _neurons.push_front(newNeuron);
  ++_numberOfNeurons;
#endif
}


