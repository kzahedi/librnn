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



#include <librnn/librnn.h>

#include <iostream>

using namespace librnn;

__Neuron_MatrixImplementation::__Neuron_MatrixImplementation()
{
  _transferfunction = NULL;
  _bias       = 0;
  _activation = 0;
  _output     = 0;
}



__Neuron_MatrixImplementation::~__Neuron_MatrixImplementation()
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.debug("This neuron is deleted");
#endif
}



void __Neuron_MatrixImplementation::updateOutput() throw(NeuronException)
{
  // TODO: needs refactoring
}



void __Neuron_MatrixImplementation::updateActivation()
{
  // TODO: needs refactoring
}



void __Neuron_MatrixImplementation::setTransferfunction(Transferfunction transferfunction)
{
  _transferfunction = transferfunction;
}

__REAL __Neuron_MatrixImplementation::transfer(__REAL x) throw(NeuronException)
{
  if(_transferfunction == NULL)
  {
    throw NeuronException("no transfer function specified");
  }
  return _transferfunction(_activation);
}


void __Neuron_MatrixImplementation::setOutput(__REAL output)
{
  _output = output;
}


__REAL __Neuron_MatrixImplementation::getOutput()
{
  return _output;
}



__REAL __Neuron_MatrixImplementation::getActivation()
{
  return _activation;
}



void __Neuron_MatrixImplementation::setActivation(__REAL activation)
{
  _activation = activation;
}



void __Neuron_MatrixImplementation::setBias(__REAL bias)
{
  _bias = bias;
}



__REAL __Neuron_MatrixImplementation::getBias()
{
  return _bias;
}



int __Neuron_MatrixImplementation::getId()
{
  return _id;
}

void __Neuron_MatrixImplementation::copy(__Neuron_MatrixImplementation *neuron)
{

}


