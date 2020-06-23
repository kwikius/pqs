// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//pq_force.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITIES_PQ_FORCE_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITIES_PQ_FORCE_HPP_INCLUDED2911030401

#include "defaults.hpp"

namespace physical_quantities{
//sequence
//Length,Time,Mass,Temperature,Current,Substance,Intensity
    template< typename Value_type>
    class pq_force{
        typedef abstract_pq<1,-2,1> zbase;
    public:  
    typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::m,
                of_time::s,
                of_mass::kg
            >,
            of_quantity::dyne_to_N
        > dyn;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::m,
                of_time::s,
                of_mass::kg
            >,
            of_quantity::lbf_to_N
        > lbf;

        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::m,
                of_time::s,
                of_mass::kg
            >
        > N;

       typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::m,
                of_time::s,
                of_mass::kg
            >,
            of_quantity::kgf_to_N
        > kgf;

       typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::m,
                of_time::s,
                of_mass::kg
            >,
            of_quantity::kN_to_N
        > kN; 
    };
    struct q_force : pq_force<pq_default_value_type>{};
}//namespace physical_quantities
#endif

