#include <librnn/librnn.h>
#include <iostream>
#include <sys/time.h>
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
  cout << "RecurrentNeuralNetwork constructor:\t";
  startTiming();
  RecurrentNeuralNetwork *rnn = new RecurrentNeuralNetwork();
  long time = stopTiming();
  printTime(time);
  delete rnn;
  return time;
}

static long testDestructor()
{
  cout << "RecurrentNeuralNetwork destructor:\t";
  RecurrentNeuralNetwork *rnn = new RecurrentNeuralNetwork();
  startTiming();
  delete rnn;
  long time = stopTiming();
  printTime(time);
  return time;
}

static long testAddNeurons()
{
  cout << "RecurrentNeuralNetwork addNeuron:\t";
  RecurrentNeuralNetwork *rnn = new RecurrentNeuralNetwork();
  startTiming();
  for(int i=0;i < 10000; i++)
  {
    Neuron *n = new Neuron();
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
}
