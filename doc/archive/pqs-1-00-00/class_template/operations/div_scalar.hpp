// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//div_scalar.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITY_CLASS_TEMPLATE_SCALAR_DIV_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITY_CLASS_TEMPLATE_SCALAR_DIV_HPP_INCLUDED2911030401

#include "../generic.hpp"

namespace physical_quantities{

        // PQ / scalar
        template
        <
            typename Abstract_pqA,
            typename Value_typeA,
            typename Units,
            quantity_mx Q_mx,
            typename Value_typeB
        >
        inline p_quantity
                <
                    Abstract_pqA,
                    typename math_promote
                    <  
                        Value_typeA,Value_typeB
                    > ::type,
                    Units,
                    Q_mx
                >
            operator / 
                (p_quantity
                 <
                    Abstract_pqA,
                    Value_typeA,
                    Units,
                    Q_mx
                 >const & pqA,
                    Value_typeB const& v)
            {
                return p_quantity
                <
                    Abstract_pqA,
                    typename math_promote
                    <
                        Value_typeA,
                        Value_typeB
                    > ::type,
                    Units,
                    Q_mx
                >(pqA() / v);
            }

    //scalar / PQ 
    template
    <
        typename Abstract_pqA,
        typename Value_typeA,
        typename Units,
        quantity_mx Q_mx,
        typename Value_typeB
    >
    inline p_quantity
           <
                typename pq_negate_powers_for_divide_by<Abstract_pqA>::type,
                typename math_promote
                <
                    Value_typeA,
                    Value_typeB
                > ::type,
                Units,
                Q_mx
           >
        operator / 
            (Value_typeB const & v,
                p_quantity
                <
                    Abstract_pqA,
                    Value_typeA,
                    Units,
                    Q_mx
                >const & pqA)
        {
            typedef p_quantity
            <
                Abstract_pqA,
                typename math_promote
                <
                    Value_typeA,Value_typeB
                > ::type,
                Units,
                of_quantity::null
            > base_type;
            base_type bA(pqA);

           return  p_quantity
           <
                typename pq_negate_powers_for_divide_by<Abstract_pqA>::type,
                typename math_promote
                <
                    Value_typeA,
                    Value_typeB
                > ::type,
                Units,
                of_quantity::null
           >( v / bA());
        }
}
#endif
