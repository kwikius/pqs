// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//defaults.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.


#ifndef PHYSICAL_QUANTITIES_DEFAULT_VALUE_TYPE_INCLUDED
#define PHYSICAL_QUANTITIES_DEFAULT_VALUE_TYPE_INCLUDED

// these macros are for testing only. Ideally one behaviour will be 
// used consistently ultimately
// provides an float to int warning on unit conversion (best I can do :-) )
//#define PHYSICAL_QUANTITIES_WARN_ON_UNIT_CONVERSIONS
// makes unit-converting ctor explicit
//#define PHYSICAL_QUANTITIES_USE_EXPLICIT_CONVERSION_CTOR

#include "../class_template/interface/interface.hpp"
#include "../class_template/abstract_pq.hpp"
#include "../class_template/generic.hpp"
#include "../class_template/operations/add_sub.hpp"
#include "../class_template/operations/div.hpp"
#include "../class_template/operations/mul.hpp"
#include "../class_template/operations/power_root.hpp"
#include "../class_template/operations/comp.hpp"
#include "../class_template/pq_unit_traits.hpp"

namespace physical_quantities{

// change Value_type for q_XXXtypes
    typedef double pq_default_value_type;

}

#endif
