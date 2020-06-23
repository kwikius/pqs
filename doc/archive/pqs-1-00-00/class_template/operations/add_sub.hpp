// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//add_sub.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITY_CLASS_TEMPLATE_ADD_SUB_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITY_CLASS_TEMPLATE_ADD_SUB_HPP_INCLUDED2911030401

#include "../generic.hpp"
#include "add_semantics.hpp"

namespace physical_quantities{

    // add two pqs of same units ,diff value_type
    template
    < 
        typename Abstract_pq,
        typename Value_typeA,
        typename Value_typeB,
        typename Units,
        quantity_mx Q_mx
    >
    inline p_quantity<
        Abstract_pq,
        typename math_promote<Value_typeA,Value_typeB>::type,
        Units,
        Q_mx
    >
        operator +(p_quantity<
                        Abstract_pq,
                        Value_typeA,
                        Units,
                        Q_mx
                    >const& pqa,
                    p_quantity<
                        Abstract_pq,
                        Value_typeB,
                        Units,
                        Q_mx
                    >const& pqb)
        {
            return p_quantity<
                        Abstract_pq,
                        typename math_promote<Value_typeA,Value_typeB>::type,
                        Units,
                        Q_mx
                    >(pqa() + pqb());
        }

    // PQ + PQ same Power different units,value_type
    template
    < 
        typename Abstract_pq,
        typename Value_typeA,
        typename UnitsA,
        quantity_mx Q_mxA,
        typename From_abstract_pq,
        typename Value_typeB,
        typename UnitsB,
        quantity_mx Q_mxB
    >
    inline  typename pq_add_semantics
            <
                Abstract_pq,
                Value_typeA,
                UnitsA,
                Q_mxA,
                Value_typeB,
                UnitsB,
                Q_mxB
            > ::return_type
        operator + (p_quantity<
                    Abstract_pq,
                    Value_typeA,
                    UnitsA,
                    Q_mxA 
                >const & a ,
                p_quantity<
                    From_abstract_pq,
                    Value_typeB,
                    UnitsB,
                    Q_mxB 
                >const& b)
        {
            //D.A.checking
            void (*pf)()
            = &DimensionallyEquivalentConcept
            <
                Abstract_pq,
                From_abstract_pq
            >;pf=pf;
 #ifdef PHYSICAL_QUANTITIES_WARN_ON_UNIT_CONVERSIONS
             void (*pf1)() = 
                &UnitConversionWarningConcept
                <
                    UnitsA,
                    Q_mxA,
                    UnitsB,
                    Q_mxB
                >;pf1=pf1;
#endif          
            typename pq_add_semantics
            <
                Abstract_pq,
                Value_typeA,
                UnitsA,
                Q_mxA,
                Value_typeB,
                UnitsB,
                Q_mxB
            > ::return_type t(a);
            return t += b;
        }

    // subtract two pqs of same units, diff value_type
    template
    < 
        typename Abstract_pq,
        typename Value_typeA,
        typename Value_typeB,
        typename Units,
        quantity_mx Q_mx
    >
    inline p_quantity<
        Abstract_pq,
        typename math_promote<Value_typeA,Value_typeB>::type,
        Units,
        Q_mx
    >
        operator-(p_quantity<
                        Abstract_pq,
                        Value_typeA,
                        Units,
                        Q_mx
                    >const& pqa,
                    p_quantity<
                        Abstract_pq,
                        Value_typeB,
                        Units,
                        Q_mx
                    >const& pqb)
        {
            return p_quantity<
                        Abstract_pq,
                        typename math_promote<Value_typeA,Value_typeB>::type,
                        Units,
                        Q_mx
                    >(pqa() - pqb());
        }

    // PQ - PQ same Power different units,Value_type
    template
    <
        typename  Abstract_pq,
        typename Value_typeA,
        typename UnitsA,
        quantity_mx Q_mxA,
        typename From_abstract_pq,
        typename Value_typeB,
        typename UnitsB,
        quantity_mx Q_mxB
    >
    inline typename pq_add_semantics
            <
                Abstract_pq,
                Value_typeA,
                UnitsA,
                Q_mxA,
                Value_typeB,
                UnitsB,
                Q_mxB
            > ::return_type
        operator - 
            (p_quantity
            <
                From_abstract_pq,
                Value_typeA,
                UnitsA,
                Q_mxA
            >const & a,
            p_quantity
            <
                Abstract_pq,
                Value_typeB,
                UnitsB,
                Q_mxB
            >const& b)
        {
            //D.A.checking
            void (*pf)()
            = &DimensionallyEquivalentConcept
            <
                Abstract_pq,
                From_abstract_pq
            >;pf=pf;
#ifdef PHYSICAL_QUANTITIES_WARN_ON_UNIT_CONVERSIONS
             void (*pf1)() = 
                &UnitConversionWarningConcept
                <
                    UnitsA,
                    Q_mxA,
                    UnitsB,
                    Q_mxB
                >;pf1=pf1;
#endif
            typename pq_add_semantics
            <
                Abstract_pq,
                Value_typeA,
                UnitsA,
                Q_mxA,
                Value_typeB,
                UnitsB,
                Q_mxB
            >::return_type t(a);
            return t -= b;
        }
}//namespace physical_quantities

#endif

