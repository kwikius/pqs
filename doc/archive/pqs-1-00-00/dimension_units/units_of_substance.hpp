// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//units_of_substance.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITIES_UNITS_OF_SUBSTANCE_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITIES_UNITS_OF_SUBSTANCE_HPP_INCLUDED2911030401

#include "dimension_unit_classes.hpp"

namespace physical_quantities{
 
    struct of_substance : dimension::of_dimension<dimension::Substance>{ 
        enum unit
        {
            null    =           0,          // alias for std unit
            mol     =           0          //standard unit
        };
        template< unit u>
        struct unit_traits : base_unit_traits<unit,u>{
            static inline float  number_of_std_units_in();
            static inline const char*const c_str();
        };
    } ; 
   
    //mol
    template<>
    inline float of_substance::unit_traits<of_substance::mol>::number_of_std_units_in()
                        {return 1.0f;}
    template<>
    inline char const*const of_substance::unit_traits<of_substance::mol>::c_str()
                        {return "mol";}
    
}

#endif
