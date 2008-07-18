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


// TODO faster implementation to remove an element from a vector
#define __REMOVE_ELEMENT_FROM_VECTOR(vec,e,i) for(i=vec.begin(); i!=vec.end(); i++) { if ( (*i) == e) { vec.erase(i); break; } }
#define __CHECK_IF_ELEMENT_IN_VECTOR(vec,e,i,r) { r = false;for(i=vec.begin(); i!=vec.end(); i++) { if ( (*i) == e) { r = true; break;} }}

#define __FOR(i,v) for(i = v.begin(); i != v.end(); i++)
#define __FOR_REVERSE(i,v) for(i = v.end(); ((v.size()==1)?i:(i+1)) != v.begin(); i--)

#define __MIN(a,b) ((a<b)?a:b)
