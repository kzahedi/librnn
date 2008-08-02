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



using namespace librnn;



Synapse::Synapse()
{
  init();
}



Synapse::Synapse(Neuron *source, Neuron *destination)
{
  init();
  _source      = source;
  _destination = _destination;
}



Synapse::Synapse(Neuron *source, Neuron *destination, __REAL strength)
{
  init();
  _strength    = strength;
  _source      = source;
  _destination = destination;
}



Synapse::~Synapse()
{
#ifdef USE_LOG4CPP_OUTPUT
  libRnnLogger.debug("this synapse is removed");
#endif // USE_LOG4CPP_OUTPUT
}



__REAL Synapse::strength() 
{
  return _strength;
}



void Synapse::setStrength(__REAL strength) 
{
  _strength = strength;
}



void Synapse::init()
{
  _strength = 0;
  _status   = __SYNAPSE_STATUS_VALID;
}



Neuron* Synapse::source()
{
  return _source;
}



Neuron* Synapse::destination()
{
  return _destination;
}


void Synapse::setStatus(int status)
{
  _status = status;
  if(_status == __SYNAPSE_STATUS_DEAD)
  {
    _strength == 0;
  }
}

int Synapse::status()
{
  return _status;
}

void Synapse::copy(Synapse *source)
{
  _status = source->status();
  _strength = source->strength();
}
