// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//pq_current.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITIES_PQ_CURRENT_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITIES_PQ_CURRENT_HPP_INCLUDED2911030401

#include "defaults.hpp"

namespace physical_quantities{
//sequence
//Length,Time,Mass,Temperature,Current,Substance,Intensity

    template< typename Value_type>
    class pq_current {
        typedef abstract_pq<0,0,0,0,1> zbase;
    public:
        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::null,
                of_time::null,
                of_mass::null,
                of_temperature::null,
                of_current::pA
            >
        > pA;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::null,
                of_time::null,
                of_mass::null,
                of_temperature::null,
                of_current::nA
            >
        > nA;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::null,
                of_time::null,
                of_mass::null,
                of_temperature::null,
                of_current::uA
            >
        > uA;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::null,
                of_time::null,
                of_mass::null,
                of_temperature::null,
                of_current::mA
            >
        > mA;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::null,
                of_time::null,
                of_mass::null,
                of_temperature::null,
                of_current::A
            >
        > A;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::null,
                of_time::null,
                of_mass::null,
                of_temperature::null,
                of_current::abampere
            >
        > abampere;
    };//pq_current
    struct q_current : pq_current<pq_default_value_type>{};
}//physical_quantities
#endif
