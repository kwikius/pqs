// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//pq_frequency.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITIES_PQ_FREQUENCY_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITIES_PQ_FREQUENCY_HPP_INCLUDED2911030401

#include "defaults.hpp"

namespace physical_quantities{
//sequence
//Length,Time,Mass,Temperature,Current,Substance,Intensity

    template< typename Value_type>
    class pq_frequency{
        typedef abstract_pq<0,-1> zbase;
    public:

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::null,
                of_time::ps
            >
        > THz;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::null,
                of_time::ns
            >
        > GHz;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::null,
                of_time::us
            >
        > MHz;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::null,
                of_time::ms
            >
        > kHz;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::null,
                of_time::s
            >
        > Hz;
    };
    struct q_frequency : pq_frequency<pq_default_value_type>{};
}//namespace physical_quantities
#endif

