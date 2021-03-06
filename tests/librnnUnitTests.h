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



#ifndef __LIBRNN_TEST_H__
#define __LIBRNN_TEST_H__

#include <librnn/librnn.h>
#include <cppunit/extensions/HelperMacros.h>

class librnnUnitTests : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(librnnUnitTests);
  CPPUNIT_TEST(testConstructor);
  CPPUNIT_TEST(testTransferfunction);
  CPPUNIT_TEST(testNoTransferfunctionException); 
  CPPUNIT_TEST(testAddingAndDeletingOfNeuronsWithNoSynapses);// passed
  CPPUNIT_TEST(testAddingAndDeletingOfSynapses);
  CPPUNIT_TEST(testAddingAndDeletingOfNeurons);
  CPPUNIT_TEST(testSingleNeuronWithOscillation);
  CPPUNIT_TEST(testRecurrentNeuralNetworkWithSingleNeuron);
#ifdef TIME_CONSUMING_TEST
  CPPUNIT_TEST(testSmallNeuroModule);
#endif // TIME_CONSUMING
  CPPUNIT_TEST(testRecurrentNeuralNetworkConversion);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void testConstructor();
  void testTransferfunction();
  void testSingleNeuronWithOscillation();
  void testNoTransferfunctionException();
  void testRecurrentNeuralNetworkWithSingleNeuron();
#ifdef TIME_CONSUMING_TEST
  void testSmallNeuroModule();
#endif // TIME_CONSUMING
  void testAddingAndDeletingOfSynapses();
  void testAddingAndDeletingOfNeurons();
  void testAddingAndDeletingOfNeuronsWithNoSynapses();
  void testRecurrentNeuralNetworkConversion();
};

#endif // __LIBRNN_TEST_H__
