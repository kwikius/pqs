// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//pq_volume.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITIES_PQ_VOLUME_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITIES_PQ_VOLUME_HPP_INCLUDED2911030401

#include "defaults.hpp"

namespace physical_quantities{
//sequence
//Length,Time,Mass,Temperature,Current,Substance,Intensity
    template< typename Value_type >

    class pq_volume { 
        typedef abstract_pq<3> zbase;
    public:
            typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::um
            >
        > um3;
        
        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::mm
            >
        > mm3;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::cm
            >
        > cm3;
        typedef cm3 mL;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
            of_length::in
            >
        > in3;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::dm
            >
        > L;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::dm
            >,
            of_quantity::us_gallon_to_L
        > us_gallon;


        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::dm
            >,
            of_quantity::imp_gallon_to_L
        > imp_gallon;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::ft
            >
        > ft3;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
            of_length::yd
            >
        > yd3;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::m
            >
        > m3;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::km
            >
        > km3;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::mi
            >
        > mi3;

          typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
            of_length::AU
            >
        > AU3;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
            of_length::l_y_
            >
        > l_y_3;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
            of_length::pc
            >
        > pc3;
    };//pq_volume
    struct q_volume : pq_volume<pq_default_value_type>{};

}//namespace physical_quantities
#endif

