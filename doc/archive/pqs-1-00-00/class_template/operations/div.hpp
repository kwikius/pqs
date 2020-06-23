// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//div.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITY_CLASS_TEMPLATE_DIV_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITY_CLASS_TEMPLATE_DIV_HPP_INCLUDED2911030401


#include "div_semantics.hpp"
#include "../generic.hpp"
#include "div_scalar.hpp"


namespace physical_quantities{
// div two pqs of same units ,diff value_type
// with of_quantity::null
// note in theory the two of_quantity multipliers could be subtracted
// to provide a result Q_mx and it may be possible to introduce this for
// SI style units, this could be further extended to dimension units
// In this version only of_quantity::null uses this specialisation
    template
    < 
        typename Abstract_pqA,
        typename Abstract_pqB,
        typename Value_typeA,
        typename Value_typeB,
        typename Units
    >
    inline p_quantity<
        typename pq_subtract_powers_for_divide<
            Abstract_pqA,
            Abstract_pqB
        >::type,
        typename math_promote<
            Value_typeA,
            Value_typeB
        >::type,
        Units
    >
        operator/(  p_quantity<
                        Abstract_pqA,
                        Value_typeA,
                        Units
                    >const& pqa,
                    p_quantity<
                        Abstract_pqB,
                        Value_typeB,
                        Units
                    >const& pqb)
        {
            return p_quantity<
            typename pq_subtract_powers_for_divide<
                Abstract_pqA,
                Abstract_pqB
            >::type,
            typename math_promote<
                Value_typeA,
                Value_typeB
            >::type,
            Units
            >(pqa() / pqb());
        }

    // PQa / PQb different powers different units

    template
    <
        typename Abstract_pqA,
        typename Value_typeA,
        typename UnitsA,
        quantity_mx     Q_mxA,
        typename Abstract_pqB,
        typename Value_typeB,
        typename UnitsB,
        quantity_mx     Q_mxB
    >
    inline typename pq_div_semantics
        <
            Abstract_pqA,
            Value_typeA,
            UnitsA,
            Q_mxA,
            Abstract_pqB,
            Value_typeB,
            UnitsB,
            Q_mxB
        >::return_type::identity
        
        operator /
            (p_quantity
            <
                Abstract_pqA,
                Value_typeA,
                UnitsA,
                Q_mxA
            >const & pqA,
            p_quantity
            <
                Abstract_pqB,
                Value_typeB,
                UnitsB,
                Q_mxB
            >const & pqB)
        {
#ifdef PHYSICAL_QUANTITIES_WARN_ON_UNIT_CONVERSIONS
             void (*pf)() = 
                &UnitConversionWarningConcept
                <
                    UnitsA,
                    Q_mxA,
                    UnitsB,
                    Q_mxB
                >;pf=pf;
#endif
            typedef pq_div_semantics
            <
                Abstract_pqA,
                Value_typeA,
                UnitsA,
                Q_mxA,
                Abstract_pqB,
                Value_typeB,
                UnitsB,
                Q_mxB
            > semantics;
           
            const static typename semantics::calc_type
                scale  =
                ( semantics::A_base_pq::template scale_from
                    <
                        typename semantics::calc_type,
                        UnitsA,
                        Q_mxA
                    >(1.0f)
                / semantics::B_base_pq::template scale_from
                    <
                        typename semantics::calc_type,
                        UnitsB,
                        Q_mxB
                    >(1.0f) )
                * ( semantics::return_type::template scale_from
                    < 
                        typename semantics::calc_type,
                        pq_unit_traits<>,
                        of_quantity::null
                    >(1.0f) ) ;
           return typename semantics::return_type::identity(  pqA() / pqB() * scale) ;
           
        }
}

#endif
