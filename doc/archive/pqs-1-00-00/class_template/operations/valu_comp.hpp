// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//valu_comp.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITY_CLASS_TEMPLATE_VAL_COMP_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITY_CLASS_TEMPLATE_VAL_COMP_HPP_INCLUDED2911030401

//compare utiliities for testing
#include "..generic.hpp"

namespace physical_quantities{
    //straight value compare
    // 0 pq == v
    // 1 pq > v
    // -1 pq < v
    template<
        typename Abstract_pq,
        typename Value_type,
        typename Units,
        quantity_mx Q_mx
    >
    int
    pq_value_compare(p_quantity<
                Abstract_pq,
                Value_type,
                Units,
                Q_mx) const& pq,
                Value_type v)
    {
        return (pq() == v)
            ? 0
            : ((pq() > v)? 1 : -1);
    }

// check pq value is in range of v* (1 +- range)
     // 0 pq == v in range()
    // 1 pq > v+range()
    // -1 pq < v-range()
    template<
        typename Abstract_pq,
        typename Value_type,
        typename Units,
        quantity_mx Q_mx
    >
    int
    pq_value_in_range(p_quantity<
                Abstract_pq,
                Value_type,
                Units,
                Q_mx) const& pq,
                Value_type v, Value_type range)
    {
        Value_type v_low  = v * (1 - range);
        Value_type v_high = v * (1 + range);
        return (pq() > v_high)
        ? 1
        :((pq() < v_low) ? -1 : 0);
    }
}
#endif


