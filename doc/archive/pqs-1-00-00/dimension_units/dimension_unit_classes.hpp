// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
// dimension_unit_classes.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITIES_DIMENSION_UNIT_CLASSES_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITIES_DIMENSION_UNIT_CLASSES_HPP_INCLUDED2911030401

#include "../class_template/interface/multiplied_log_enum.hpp"

// class template for units of a dimension

namespace physical_quantities{

    struct dimension{
      
        enum Id{
            Unknown,
            Length          = 1,
            Time            = 2,
            Mass            = 4,
            Temperature     = 8,
            Current         = 16,
            Substance       = 32,
            Intensity       = 64
        }; 
        template<Id D>
        struct of_dimension{
            template<typename U, U u>
            struct base_unit_traits : multiplied_log_enum<U,u>{
            };
        };  

   }; //dimension
   
}// physical_quantities
#endif
