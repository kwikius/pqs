// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//pq_accleration.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITIES_PQ_ACCELERATION_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITIES_PQ_ACCELERATION_HPP_INCLUDED2911030401

#include "defaults.hpp"

namespace physical_quantities{
//sequence
//Length,Time,Mass,Temperature,Current,Substance,Intensity

    template< typename Value_type>
    class pq_acceleration {
        typedef abstract_pq<1,-2> zbase;
    public:
        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::ft,
                of_time::s
            >
        > ft_div_s2;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::m,
                of_time::s
            >
        > m_div_s2;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::km,
                of_time::s
            >
        > km_div_s2;
        
        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::mi,
                of_time::s
            >
        > mi_div_s2;
      
        struct SI{
        // use of constants requires  compilation of source
            // in pq_acceleration.cpp
            static m_div_s2 const g;
        };
    };
    struct q_acceleration : pq_acceleration<pq_default_value_type>{};
}//namespace physical_quantities
#endif

