#include <librnn/librnn.h>
#include <iostream>
#include <sys/time.h>
#include <sys/resource.h>
#include <time.h>
#include <vector>

#include <timing.hpp>

using namespace std;
using namespace librnn;

#ifdef USE_LOG4CPP_OUTPUT
static long testInitLogger()
{
  cout << "Logger initialisation:" << endl;
  startTiming();
  initLogger();
  long time = stopTiming();
  printTime(time);
  return time;
}
#endif

static long testConstructor()
{
  cout << "RecurrentNeuralNetwork constructor:\t\t";
  startTiming();
  RecurrentNeuralNetwork *rnn = new RecurrentNeuralNetwork();
  long time = stopTiming();
  printTime(time);
  delete rnn;
  return time;
}

static long testDestructor()
{
  cout << "RecurrentNeuralNetwork destructor:\t\t";
  RecurrentNeuralNetwork *rnn = new RecurrentNeuralNetwork();
  startTiming();
  delete rnn;
  long time = stopTiming();
  printTime(time);
  return time;
}

static long testAddNeurons()
{
  cout << "RecurrentNeuralNetwork addNeuron (1M adds):\t";
  RecurrentNeuralNetwork *rnn = new RecurrentNeuralNetwork();
  startTiming();
  for(int i=0;i < 1000000; i++)
  {
    Neuron *n = new Neuron();
    rnn->addNeuron(n);
  }
  long time = stopTiming();
  printTime(time);
  delete rnn;
  return time;
}

static long testAddSynapses()
{
  cout << "RecurrentNeuralNetwork addSynapses (1M adds):\t";
  RecurrentNeuralNetwork *rnn = new RecurrentNeuralNetwork();
  startTiming();
  for(int i=0;i < 1000; i++)
  {
    Neuron *n = new Neuron();
    for(int j=0;j < 1000; j++)
    {
      Synapse *s = new Synapse();
      n->addAdjacentSynapse(s);
    }
    rnn->addNeuron(n);
  }
  long time = stopTiming();
  printTime(time);
  delete rnn;
  return time;
}



int main()
{
  cout << "starting librnn runtime test." << endl;
#ifdef USE_LOG4CPP_OUTPUT
  testInitLogger();
#endif
  testConstructor();
  testDestructor();
  testAddNeurons();
  testAddSynapses();
}
