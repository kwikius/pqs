// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//units_out.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITY_CLASS_TEMPLATE_UNITS_OUT_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITY_CLASS_TEMPLATE_UNITS_OUT_HPP_INCLUDED2911030401

#include "./interface/interface.hpp"

namespace physical_quantities{

    // utility class used for output of units of a physical quantity
    // which can be overloaded for special units
    // e.g "N" (newtons),"kgf" (kilograms force )
    template
    <   
        typename Abstract_pq,
        typename Units,
        quantity_mx Q_mx
    >
    class physical_quantity_units_out{    
    };

//.............................................................
    // utility class used for output of units of a physical quantity  as
    // dub * scale version
    // e.g "kg.m.s-2" (newtons), "kg.m.s-2 * 9.8" (kilograms force )
    template
    <
        typename Abstract_pq,
        typename Units,
        quantity_mx Q_mx
    > 
    class physical_quantity_dub_units_out{    
    };
}
#endif

