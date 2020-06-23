// physical_quantities pqs-1-00-00 03:50 29/11/2003
//tests.cpp
// feedback to andy@servocomm.freeserve.co.uk
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#include "tests.hpp"

int PhysicalQuantitiesTest()
{
    if (Constructors() !=PHYSICAL_QUANTITIES_TEST_SUCCESS)
         return PHYSICAL_QUANTITIES_TEST_FAIL;
    if (DeclareBaseVariables() !=PHYSICAL_QUANTITIES_TEST_SUCCESS)
         return PHYSICAL_QUANTITIES_TEST_FAIL;
    if (DeclareMechanicsVariables() != PHYSICAL_QUANTITIES_TEST_SUCCESS)
        return PHYSICAL_QUANTITIES_TEST_FAIL;
    if(CompareVariablesSameUnits() !=  PHYSICAL_QUANTITIES_TEST_SUCCESS)
         return PHYSICAL_QUANTITIES_TEST_FAIL;
    if (CompareVariablesDifferentUnits() !=  PHYSICAL_QUANTITIES_TEST_SUCCESS)
         return PHYSICAL_QUANTITIES_TEST_FAIL;
    if(AddSubVariablesSameUnits()!=  PHYSICAL_QUANTITIES_TEST_SUCCESS)
         return PHYSICAL_QUANTITIES_TEST_FAIL;
    if(AddSubVariablesDifferentUnits()!=  PHYSICAL_QUANTITIES_TEST_SUCCESS)
         return PHYSICAL_QUANTITIES_TEST_FAIL;
    if(MulVariablesSameUnits()!=  PHYSICAL_QUANTITIES_TEST_SUCCESS)
         return PHYSICAL_QUANTITIES_TEST_FAIL;
    if(MulVariablesDifferentUnits()!=  PHYSICAL_QUANTITIES_TEST_SUCCESS)
         return PHYSICAL_QUANTITIES_TEST_FAIL;
    if(PowerRoot()!=  PHYSICAL_QUANTITIES_TEST_SUCCESS)
         return PHYSICAL_QUANTITIES_TEST_FAIL;

    return  PHYSICAL_QUANTITIES_TEST_SUCCESS;
}
