// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//mul_scalar.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITY_CLASS_TEMPLATE_SCALAR_MUL_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITY_CLASS_TEMPLATE_SCALAR_MUL_HPP_INCLUDED2911030401

#include "../generic.hpp"

namespace physical_quantities{
        // PQ * scalar
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
            operator * 
                (p_quantity
                 <
                    Abstract_pqA,
                    Value_typeA,
                    Units,
                    Q_mx
                 >const & pqA,
                    Value_typeB const& v)
            {
                p_quantity
                <
                    Abstract_pqA,
                    typename math_promote
                    <
                        Value_typeA,
                        Value_typeB
                    > ::type,
                    Units,
                    Q_mx
                > t(pqA());
                return  t*= v;
            }

    //scalar * PQ 
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
                    Value_typeA,
                    Value_typeB
                > ::type,
                Units,
                Q_mx
           >
        operator * 
            (Value_typeB const & v,
                p_quantity
                <
                    Abstract_pqA,
                    Value_typeA,
                    Units,
                    Q_mx
                >const & pqA)
        {
            return   p_quantity
            <
                Abstract_pqA,
                typename math_promote
                <
                    Value_typeA,Value_typeB
                > ::type,
                Units,
                Q_mx
            > ( v * pqA() );
        }
}
#endif
