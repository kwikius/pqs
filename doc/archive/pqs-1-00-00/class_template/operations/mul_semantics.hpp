// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//mul_semantics.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITY_CLASS_TEMPLATE_MUL_SEMANTICS_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITY_CLASS_TEMPLATE_MUL_SEMANTICS_HPP_INCLUDED2911030401

#include "../abstract_pq.hpp"
#include "../interface/interface.hpp"
#include "../pq_unit_traits.hpp"
#include "../mpl_like/math_promote.hpp"


namespace physical_quantities{

    template
    <
        typename Abstract_pqA,
        typename Value_typeA,
        typename UnitsA,
        quantity_mx Q_mxA,
        typename Abstract_pqB,
        typename Value_typeB,
        typename UnitsB,
        quantity_mx Q_mxB
    >
    struct pq_mul_semantics{
        //calc the scaling of each pq
        static long const   scaleA 
        = (of_length::template unit_traits<UnitsA::u_length::value>::value_as_long
            * Abstract_pqA::pwr_length)
        + (of_time::template unit_traits<UnitsA::u_time::value>::value_as_long 
            * Abstract_pqA::pwr_time) 
        + (of_mass::template unit_traits<UnitsA::u_mass::value>::value_as_long 
            * Abstract_pqA::pwr_mass)
        + (of_temperature::template unit_traits<UnitsA::u_temperature::value>::value_as_long 
            * Abstract_pqA::pwr_temperature)
        + (of_current::template unit_traits<UnitsA::u_current::value>::value_as_long 
            * Abstract_pqA::pwr_current)
        + (of_substance::template unit_traits<UnitsA::u_substance::value>::value_as_long 
            * Abstract_pqA::pwr_substance)
        + (of_intensity::template unit_traits<UnitsA::u_intensity::value>::value_as_long 
            * Abstract_pqA::pwr_intensity)
        + of_quantity::template mx_traits<Q_mxA>::value_as_long ;  

        static long const   scaleB
        = (of_length::template unit_traits<UnitsB::u_length::value>::value_as_long
            * Abstract_pqB::pwr_length)
        + (of_time::template unit_traits<UnitsB::u_time::value>::value_as_long 
            * Abstract_pqB::pwr_time) 
        + (of_mass::template unit_traits<UnitsB::u_mass::value>::value_as_long 
            * Abstract_pqB::pwr_mass)
        + (of_temperature::template unit_traits<UnitsB::u_temperature::value>::value_as_long
            * Abstract_pqB::pwr_temperature)
        + (of_current::template unit_traits<UnitsB::u_current::value>::value_as_long
            * Abstract_pqB::pwr_current)
        + (of_substance::template unit_traits<UnitsB::u_substance::value>::value_as_long
            * Abstract_pqB::pwr_substance)
        + (of_intensity::template unit_traits<UnitsB::u_intensity::value>::value_as_long
            * Abstract_pqB::pwr_intensity)
        + of_quantity::template mx_traits<Q_mxB>::value_as_long ; 

        static bool const A_is_better = ( scaleA <= scaleB );

        // derive units of return type
#ifdef PHYSICAL_QUANTITIES_NO_BOOST_LIBRARY
        typedef typename if_c
#else
        typedef typename boost::mpl::if_c
#endif   
        <
            A_is_better,
            UnitsA,
            UnitsB
        >::type units_type;
        
        // determine the Value_type of return type
        typedef  typename math_promote
        < 
            Value_typeA,Value_typeB
        >::type   value_type;

        // nudge calc type to a minimum of float
        typedef typename math_promote
        <
            value_type,float 
        > ::type  calc_type;
        
        // return type for multiply
        typedef p_quantity
        <
            typename pq_add_powers_for_multiply
            <
                Abstract_pqA,Abstract_pqB
            >::type,
            value_type,
            units_type,
            of_quantity::null
        >  return_type;

        // A common for calc
        typedef p_quantity
        <
            Abstract_pqA,
            value_type,
            pq_unit_traits<>,
            of_quantity::null
        >   base_typeA;
        
        // B common for calc
        typedef p_quantity
        <
            Abstract_pqB,
            value_type,
            pq_unit_traits<>,
            of_quantity::null
        >  base_typeB;    
    };
}
#endif
