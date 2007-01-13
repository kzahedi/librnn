#ifndef __TIMING_HPP__
#define __TIMING_HPP__

#include <iostream>

using namespace std;

static long _startTime = -1;

static long getMilliseconds()
{
  timeval time;

  gettimeofday(&time, 0);   

  return ((time.tv_sec%10000) * 1000 + time.tv_usec / 1000);
}

static long getMicroseonds()
{
  timeval time;

  gettimeofday(&time, 0);   

  return ((time.tv_sec%10000) * 1000000 + time.tv_usec);
}

static long getTime()
{
  return getMicroseonds();
}


static void startTiming()
{
  _startTime = getTime();
}

static long stopTiming()
{
  if(_startTime < 0)
  {
    cerr << "forgot to call startTiming" << endl;
  }
  long result = getTime() - _startTime;
  _startTime = -1;
  return result;
}

static void printTime(long time)
{
  cout << "time elapsed: " << time << "mu-s" << endl;
}

#endif // __TIMING_HPP__
