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



#ifndef __SYNAPSE_H__
#define __SYNAPSE_H__

#define __SYNAPSE_STATUS_VALID 0
#define __SYNAPSE_STATUS_DEAD  1

#include <librnn/librnn.h>

namespace librnn
{
  class Synapse
  {
    public:
      Synapse();
      ~Synapse();

      Synapse(Neuron *source, Neuron *destination);
      Synapse(Neuron *source, Neuron *destination, __REAL strength);

      Neuron* source();
      Neuron* destination();

      void setStatus(int status);
      int status();

      __REAL strength();
      void setStrength(__REAL strength);

      void copy(Synapse *source);

    private:
      void init();

      Neuron *_source;
      Neuron *_destination;

      double _strength;
      int    _status;
  };
}

#endif // __SYNAPSE_H__
