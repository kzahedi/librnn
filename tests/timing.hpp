/**************************************************************************
 *                                                                        *
 * This file is part of librnn. Copyright (C) 2003-2006 Keyan Zahedi.     *
 * All rights reserved. Email: keyan@users.sourceforge.net                *
 * Web: http://sourceforge.net/projects/librnn                            *
 *                                                                        *
 * For a list of contributors see the file AUTHORS.                       *
 *                                                                        *
 * librnn is free software; you can redistribute it and/or modify it      *
 * under the terms of the GNU General Public License as published by the  *
 * Free Software Foundation; either version 2 of the License, or (at      *
 * your option) any later version.                                        *
 *                                                                        *
 * librnn is distributed in the hope that it will be useful, but WITHOUT  *
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or  *
 * FITNESS __FOR A PARTICULAR PURPOSE.                                      *
 *                                                                        *
 * You should have received a copy of the GNU General Public License      *
 * along with librnn in the file COPYING; if not, write to the Free       *
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA     *
 * 02110-1301, USA.                                                       *
 *                                                                        *
 **************************************************************************/



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
  cout << ((double)time/1000.0) << "ms" << endl;
}

#endif // __TIMING_HPP__
