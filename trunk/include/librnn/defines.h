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
 * FITNESS FOR A PARTICULAR PURPOSE.                                      *
 *                                                                        *
 * You should have received a copy of the GNU General Public License      *
 * along with librnn in the file COPYING; if not, write to the Free       *
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA     *
 * 02110-1301, USA.                                                       *
 *                                                                        *
 **************************************************************************/



#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <librnn/config.h>

//#include <values.h>

// using float or double precision
#ifdef USE_FLOAT_PRECISION
#define __REAL float
#elif USE_DOUBLE_PRECISION
#define __REAL double
#else
#error You must #define USE_FLOAT_PRECISION or USE_DOUBLE_PRECISION 
#endif

// using vector as container class
using namespace std;
#include <vector>

// transfer-function function pointer
typedef __REAL (*Transferfunction) (__REAL);

#define __vSYNAPSE vector<Synapse*>
#define __vNEURON  vector<Neuron*>

#define __vSYNAPSE_ITERATOR vector<Synapse*>::iterator
#define __vNEURON_ITERATOR  vector<Neuron*>::iterator

//forward declaration, such that synapses and neurons can reference each other
namespace librnn 
{
  class Synapse;
  class Neuron;
}

static int numberOfNeurons = 0;

#endif //__DEFINES_H__
