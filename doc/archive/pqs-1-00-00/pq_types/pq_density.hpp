

//  Copyright (C) Andy Little, White Light Device 2003.
//  This copyright notice shall appear in any copy of this software.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITIES_PQ_DENSITY_HPP_INCLUDED
#define PHYSICAL_QUANTITIES_PQ_DENSITY_HPP_INCLUDED

#include "defaults.hpp"

namespace physical_quantities{
//sequence
//Length,Time,Mass,Temperature,Current,Substance,Intensity
    template<typename Value_type>
    class pq_density{
        typedef abstract_pq<-3,0,1> zbase ;
    public:
        typedef p_quantity<
            zbase,Value_type,
            pq_unit_traits<
                of_length::m,
                of_time::null,
                of_mass::kg
            >
        >kg_div_m3;
    };
    struct q_density : pq_density<pq_default_value_type>{};
}//namespace physical_quantities
#endif

