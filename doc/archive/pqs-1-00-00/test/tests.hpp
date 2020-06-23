// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//tests.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITY_TESTS_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITY_TESTS_HPP_INCLUDED2911030401

#define PHYSICAL_QUANTITIES_TEST_SUCCESS    1
#define PHYSICAL_QUANTITIES_TEST_FAIL       0

#include <iostream>
#include "../pq_types/pq_all_types.hpp"
#include "../util/utility_output.hpp"

inline const char*const pqs_version(){return "pqs-1-00-00";}

int Constructors();
int PhysicalQuantitiesTest();
int DeclareLengths();
int DeclareTimes();
int DeclareMasses();
int DeclareTemperatures();
int DeclareCurrents();
int DeclareSubstance();
int DeclareIntensity();
int DeclareAreas();
int DeclareVolumes();
int DeclareFrequencies();
int DeclareVelocities();
int DeclareAccelerations();
int DeclareForces();
int DeclarePowers();
int DeclareEnergies();
int DeclarePressures();
int DeclareMechanicsVariables();
int DeclareBaseVariables();
int CompareVariablesDifferentUnits();
int CompareVariablesSameUnits();
int PowerRoot();
int MulVariablesSameUnits();
int AddSubVariablesDifferentUnits();
int AddSubVariablesSameUnits();
int MulVariablesDifferentUnits();
int MulVariablesSameUnits();

//2nd batch todo
int ADDVariables(std::ostream& os);

#endif
