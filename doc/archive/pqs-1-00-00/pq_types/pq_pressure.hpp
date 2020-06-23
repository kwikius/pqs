// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//pq_pressure.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITIES_PQ_PRESSURE_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITIES_PQ_PRESSURE_HPP_INCLUDED2911030401

#include "defaults.hpp"

namespace physical_quantities{
//sequence
//Length,Time,Mass,Temperature,Current,Substance,Intensity
    template< typename Value_type>
    class pq_pressure {
        typedef abstract_pq<-1,-2,1> zbase;
    public:

        typedef p_quantity <
            zbase,Value_type,
            pq_unit_traits<
                of_length::m,
                of_time::s,
                of_mass::kg
            >
        > Pa;

        typedef p_quantity <
            zbase,Value_type,
            pq_unit_traits<
                of_length::m,
                of_time::s,
                of_mass::kg
            >,
            of_quantity::mx_1e2
        > mbar;

         typedef p_quantity <
            zbase,Value_type,
            pq_unit_traits<
                of_length::m,
                of_time::s,
                of_mass::kg
            >,
            of_quantity::mx_1e3
        > kPa;

        typedef p_quantity <
            zbase,Value_type,
            pq_unit_traits<
                of_length::m,
                of_time::s,
                of_mass::kg
            >,
            of_quantity::psi_to_Pa
        >psi;

        typedef p_quantity <
            zbase,Value_type,
            pq_unit_traits<
                of_length::m,
                of_time::s,
                of_mass::kg
            >,
            of_quantity::mx_1e5
        > bar;

        typedef p_quantity <
            zbase,Value_type,
            pq_unit_traits<
                of_length::m,
                of_time::s,
                of_mass::kg
            >,
            of_quantity::mx_1e6
        > MPa;
    };
    struct q_pressure : pq_pressure<pq_default_value_type>{};
}
#endif
