// physical_quantities pqs-1-00-00 03:50 29/11/2003
//main.cpp
// feedback to andy@servocomm.freeserve.co.uk
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#include "tests.hpp"
#include <iostream>

int main()
{
    if ( PhysicalQuantitiesTest() !=  PHYSICAL_QUANTITIES_TEST_SUCCESS){
        std::cout << "Test failed\n";
        return PHYSICAL_QUANTITIES_TEST_FAIL;
    }
    std::cout << "test succeeded\n";
    return PHYSICAL_QUANTITIES_TEST_SUCCESS;
}


