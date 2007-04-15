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



#include <librnn/Synapse.h>

using namespace librnn;

Synapse::Synapse()
{
  init();
}

Synapse::~Synapse()
{

}

Synapse::Synapse(Neuron *source, Neuron *destination)
{
  init();
  _source      = source;
  _destination = _destination;
}

Synapse::Synapse(Neuron *source, Neuron *destination, REAL strength)
{
  _strength    = strength;
  _source      = source;
  _destination = destination;
}


REAL Synapse::strength() 
{
  return _strength;
}

void Synapse::init()
{
  _strength = 0;
}

Neuron* Synapse::source()
{
  return _source;
}

Neuron* Synapse::destination()
{
  return _destination;
}
