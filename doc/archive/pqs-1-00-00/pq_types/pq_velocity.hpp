// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//pq_velocity.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITIES_PQ_VELOCITY_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITIES_PQ_VELOCITY_HPP_INCLUDED2911030401

#include "defaults.hpp"

namespace physical_quantities{
//sequence
//Length,Time,Mass,Temperature,Current,Substance,Intensity
    template< typename Value_type>
    class pq_velocity {
        typedef abstract_pq<1,-1> zbase;
    public:
         typedef p_quantity<
            zbase, Value_type,
            pq_unit_traits<
                of_length::mm,
                of_time::min
            >
        > mm_div_min;

         typedef p_quantity<
            zbase, Value_type,
            pq_unit_traits<
                of_length::mm,
                of_time::s
            >
        > mm_div_s;

         typedef p_quantity<
            zbase, Value_type,
            pq_unit_traits<
            of_length::ft,
                of_time::s
            >
        > ft_div_s;


        typedef p_quantity<
            zbase, Value_type,
            pq_unit_traits<
                of_length::km,
                of_time::h
            >
        > km_div_h;

        typedef p_quantity<
            zbase, Value_type,
            pq_unit_traits<
                of_length::mi,
                of_time::h
            >
        > mi_div_h;

        typedef p_quantity<
            zbase, Value_type,
            pq_unit_traits<
                of_length::m,
                of_time::s
            >
        > m_div_s;
    };
    struct q_velocity : pq_velocity<pq_default_value_type>{};   

}//namespace physical_quantities
#endif

