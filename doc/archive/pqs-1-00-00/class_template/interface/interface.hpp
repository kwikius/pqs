// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//interface.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

// forward declaration of the p_quantity class template

#ifndef PHYSICAL_QUANTITY_INTERFACE_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITY_INTERFACE_HPP_INCLUDED2911030401

#include "../../quantity_units/of_quantity.hpp"
#include "../../dimension_units/dimension_units.hpp"

namespace physical_quantities{
 
    typedef of_quantity::mx_id quantity_mx;

    typedef of_length::unit unit_of_length;
    typedef of_time::unit unit_of_time;
    typedef of_mass::unit unit_of_mass;
    typedef of_temperature::unit unit_of_temperature;
    typedef of_current::unit unit_of_current;
    typedef of_substance::unit unit_of_substance;
    typedef of_intensity::unit unit_of_intensity;
   
    //the p_quantity class
    template
    <
        typename Abstract_pq,
        typename Value_type,
        typename Units,
        quantity_mx Q_mx = of_quantity::null
    >
    class p_quantity;
 
}//namespace physical_quantities
#endif

//Revision
