// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//utility_output.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITIES_UTILITY_OUTPUT_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITIES_UTILITY_OUTPUT_HPP_INCLUDED2911030401

//utility output  of a physical_quantity for demo purposes
//useage
//pq is physical_quantity
//os << pq ;
//outputs value of pq and units
#include <iostream>
#include "aux_units_out.hpp"

namespace physical_quantities{

    template
    <
        typename Abstract_pq,
        typename Value_type,
        typename Units,
        quantity_mx Q_mx
    >
            inline std::ostream& 
                operator << 
                    (std::ostream& os,
                        p_quantity
                        <
                            Abstract_pq,
                            Value_type,
                            Units,
                            Q_mx
                        > const& pq )
                {
                    os << pq() << ' ' << units(pq);
                    return os;
                }
}
#endif


    

