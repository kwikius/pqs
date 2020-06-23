// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//pq_area.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITIES_PQ_AREA_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITIES_PQ_AREA_HPP_INCLUDED2911030401

#include "defaults.hpp"

namespace physical_quantities{
//sequence
//Length,Time,Mass,Temperature,Current,Substance,Intensity
    template< typename Value_type>
    class pq_area {
        typedef abstract_pq<2> zbase;
    public:
        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::um
            >
        > um2;
        
        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::mm
            >
        > mm2;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::cm
            >
        > cm2;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
            of_length::in
            >
        > in2;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::ft
            >
        > ft2;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
            of_length::yd
            >
        > yd2;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::m
            >
        > m2;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::km
            >
        > km2;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::mi
            >
        > mi2;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
            of_length::AU
            >
        > AU2;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
            of_length::l_y_
            >
        > l_y_2;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
            of_length::pc
            >
        > pc2;  
    };
    struct q_area : pq_area<pq_default_value_type>{};
}
#endif

