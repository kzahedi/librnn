#include <librnn/librnn.h>

#include <utility>                   // for std::pair
#include <algorithm>                 // for std::for_each
#include <boost/graph/dijkstra_shortest_paths.hpp>


using namespace std;

RecurrentNeuralNetwork::RecurrentNeuralNetwork()
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.debug("constructor called");
#endif
  _numberOfSynapses = -1;
  _numberOfNeurons  = -1;
}

RecurrentNeuralNetwork::~RecurrentNeuralNetwork()
{
}

void RecurrentNeuralNetwork::init(int numberOfNeurons, int numberOfSynapses)
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.debug("number of neurons : %d", numberOfNeurons);
  libRnnLogger.debug("number of synapses: %d", numberOfSynapses);
#endif
}

int RecurrentNeuralNetwork::getNumberOfNeurons()
{
  return _numberOfNeurons;
}

int RecurrentNeuralNetwork::getNumberOfSynapses()
{
  return _numberOfSynapses;
}
