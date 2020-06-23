//  Copyright (C) Andy Little, White Light Device 2003.
//  This copyright notice shall appear in any copy of this software.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

// template and instructions for creating defining physical quantities and units

#ifndef PHYSICAL_QUANTITIES_PQ_@QUANTITYNAME@_HPP_INCLUDED
#define PHYSICAL_QUANTITIES_PQ_@QUANTITYNAME@_HPP_INCLUDED

#include "physical_quantities_defaults.hpp"

namespace physical_quantities{
// where dimensions are in sequences this is the sequence used
//Length,Time,Mass,Temperature,Current,Substance,Intensity

    template< typename Value_type>
    class pq_@QUANTITYNAME@ {
  // insert  ^^^  name for the type here voltage,inductance etc

        typedef abstract_pq<@,@,@,@,@,@,@> zbase;
 // insert powers of dimension ^^^^^  here using the sequence list above
// (literal ints)
    public:
         typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
            
            // replace nulls below with your units if necessary,
            // nulls ok on no unit
            // (ok to use default params)
                of_length::null,      // "../dimension_units/units_of_length.hpp"
                of_time::null,        // "../dimension_units/units_of_time.hpp"
                of_mass::null,        // "../dimension_units/units_of_length.hpp"
                of_temperature::null, // "../dimension_units/units_of_temperature.hpp"
                of_current::null,     // "../dimension_units/units_of_current.hpp"
                of_substance::null,   // "../dimension_units/units_of_substance.hpp"
                of_intensity::null    // "../dimension_units/units_of_intensity.hpp"
            >,
            of_quantity::null       // ..quantity_units/of_quantity.hpp
        // replace with   ^^^  your quantity unit if necessary else null ok
        // (ok to use default param)
        > @QUANTITYUNIT@;
  //name  ^^^ your unit(s) here

     //... next unit typedef... etc

    };
// derived quantity container(one of) for cooler keyboard :-)
    struct q_@QUANTITYNAME@ : pq_@QUANTITYNAME@<pq_default_value_type>{};
                                    //pq_default_value_type typedefed in
                                    //"./physical_quantities_defaults.hpp"
                                    // default is double  
                                
}//namespace physical-quantities
#endif

