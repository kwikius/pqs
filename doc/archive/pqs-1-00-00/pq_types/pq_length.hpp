// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//pq_length.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  This copyright notice shall appear in any copy zbase this software.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITIES_PQ_LENGTH_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITIES_PQ_LENGTH_HPP_INCLUDED2911030401

#include "defaults.hpp"

namespace physical_quantities{
//sequence
//Length,Time,Mass,Temperature,Current,Substance,Intensity
    template< typename Value_type>
    class pq_length {
        typedef abstract_pq<1> zbase ;
    public:

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::nm
            >
        > nm;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::um
            >
        > um;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::mm
            >
        > mm;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::cm
            >
        > cm;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
            of_length::in
            >
        > in;
        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::dm
            >
        > dm;


        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
            of_length::ft
            >
        > ft;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
            of_length::yd
            >
        > yd;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::m
            >
        > m;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::km
            >
        > km;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::mi
            >
        > mi;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
            of_length::AU
            >
        > AU;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::l_y_
            >
        > l_y_;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::pc
            >
        > pc;
    };//class  pq_length

    //pq_length with pq_default_value_type
    struct q_length : pq_length<pq_default_value_type>{};
    

}//namespace physical_quantities


#endif
