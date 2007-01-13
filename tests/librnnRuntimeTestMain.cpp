#include <librnn/librnn.h>
#include <sys/time.h>
#include <time.h>
#include <vector>

#include <iostream.h>

#include <timing.hpp>

static long testInitLogger()
{
  cout << "Logger initialisation:" << endl;
  startTiming();
  initLogger();
  long time = stopTiming();
  printTime(time);
  return time;
}
static long testConstructor()
{
  cout << "RecurrentNeuralNetwork constructor:" << endl;
  startTiming();
  RecurrentNeuralNetwork *rnn = new RecurrentNeuralNetwork();
  long time = stopTiming();
  printTime(time);
  delete rnn;
  return time;
}

static long testDestructor()
{
  cout << "RecurrentNeuralNetwork destructor:" << endl;
  RecurrentNeuralNetwork *rnn = new RecurrentNeuralNetwork();
  startTiming();
  delete rnn;
  long time = stopTiming();
  printTime(time);
  return time;
}


int main()
{
  cout << "starting librnn runtime test" << endl;
  testInitLogger();
  testConstructor();
  testDestructor();
}
