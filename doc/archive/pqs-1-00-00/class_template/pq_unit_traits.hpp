// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//pq_unit_traits.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITIES_PQ_UNIT_TRAITS_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITIES_PQ_UNIT_TRAITS_HPP_INCLUDED2911030401

#include "interface/interface.hpp"

namespace physical_quantities {
//sequence
//Length,Time,Mass,Temperature,Current,Substance,Intensity
     template
    <
        unit_of_length U_len = of_length::null,
        unit_of_time U_time = of_time::null,
        unit_of_mass U_mass = of_mass::null,
        unit_of_temperature U_temp = of_temperature::null,
        unit_of_current U_current = of_current::null,
        unit_of_substance U_subst = of_substance::null,
        unit_of_intensity U_intens = of_intensity::null
    >
    struct pq_unit_traits{

       typedef of_length::unit_traits<U_len>       u_length;
       typedef of_time::unit_traits<U_time>        u_time;
       typedef of_mass::unit_traits<U_mass>        u_mass;
       typedef of_temperature::unit_traits<U_temp> u_temperature;
       typedef of_current::unit_traits<U_current>   u_current;
       typedef of_substance::unit_traits<U_subst>   u_substance;
       typedef of_intensity::unit_traits<U_intens>  u_intensity;
    };

}//namespace physical_quantities


#endif

