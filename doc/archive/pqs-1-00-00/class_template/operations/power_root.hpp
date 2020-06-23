// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//power_root.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITY_CLASS_TEMPLATE_POWER_ROOT_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITY_CLASS_TEMPLATE_POWER_ROOT_HPP_INCLUDED2911030401

#include <cmath>
#include "../generic.hpp"
namespace physical_quantities{

    template 
    <
        int Power,
        typename Abstract_pq,
        typename Value_type,
        typename Units,
        quantity_mx Q_mx 
    >
    inline typename p_quantity
           <
                typename pq_multiply_power_for_exp
                <
                    Abstract_pq,
                    Power
                > ::type,
                Value_type,
                Units,
                of_quantity::null
           > ::identity
         power( p_quantity
                <
                    Abstract_pq,
                    Value_type,
                    Units,
                    Q_mx
                > const & pq )
        {
                //scale to dub temp
               Value_type v = p_quantity
                <
                    Abstract_pq,
                    Value_type,
                    Units,
                    of_quantity::null
                >::template scale_from
                    <
                        Value_type,
                        Units,
                        Q_mx
                    >(pq());
               
                return typename p_quantity
                <
                    typename pq_multiply_power_for_exp
                    <
                        Abstract_pq,
                        Power
                    >::type,
                    Value_type,
                    Units,
                    of_quantity::null
                >::identity( std::pow(v,Power) );
        }
 
     //root
     //useage root<MyPower>(pq)
     //each power in the pq must be divisible by MyPower with no remainder
     //the wrong return type is generated at compile time
     //if this condition is not met.
    template
    <
        int Pow,
        typename Abstract_pq,
        typename Value_type,
        typename Units,
        quantity_mx Q_mx
    >
    inline typename p_quantity
    <
        typename pq_divide_power_for_exp
        <
            Abstract_pq,
            Pow
        > ::type,
        Value_type,
        Units,
        of_quantity::null
    >::identity
        root( p_quantity
              <
                Abstract_pq,
                Value_type,
                Units,
                Q_mx
              > const & pq)
        {
            //scale to dub
            p_quantity
            <
                Abstract_pq,
                Value_type,
                Units,
                of_quantity::null
            > t(pq);

            //best type for division
            typedef typename math_promote
            <
                Value_type,float
            >::type calc_value_type;

            return typename p_quantity
            <
            typename pq_divide_power_with_remainder_for_exp
                <
                    Abstract_pq,
                    Pow
                >::type,
                Value_type,
                Units,
                of_quantity::null
            >::identity( std::pow(static_cast<Value_type>(t()),
                1.0f/static_cast<calc_value_type>(Pow) ) );
        }
}

#endif

