// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//add_semantics.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITY_CLASS_TEMPLATE_ADD_SEMANTICS_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITY_CLASS_TEMPLATE_ADD_SEMANTICS_HPP_INCLUDED2911030401

#include "../interface/interface.hpp"
#include "../mpl_like/boost_lib_dependencies.hpp"
#ifdef PHYSICAL_QUANTITIES_NO_BOOST_LIBRARY
#include "../mpl_like/if.hpp"
#else
#include "boost/mpl/if.hpp"
#endif

#include "../mpl_like/math_promote.hpp"

namespace physical_quantities{

    template
    <
        typename Abstract_pq,
        typename Value_typeA,
        typename UnitsA,
        quantity_mx Q_mxA,
        typename Value_typeB,
        typename UnitsB,
        quantity_mx Q_mxB
    >
    struct pq_base_add_semantics{
    
        //calc the scaleing of each pq
        static long const   scaleA
        = (of_length::template unit_traits<UnitsA::u_length::value>::value_as_long
            * Abstract_pq::pwr_length)
        + (of_time::template unit_traits<UnitsA::u_time::value>::value_as_long
            * Abstract_pq::pwr_time) 
        + (of_mass::template unit_traits<UnitsA::u_mass::value>::value_as_long
            * Abstract_pq::pwr_mass) 
        + (of_temperature::template unit_traits<UnitsA::u_temperature::value>::value_as_long
            * Abstract_pq::pwr_temperature)
        + (of_current::template unit_traits<UnitsA::u_current::value>::value_as_long
            * Abstract_pq::pwr_current)
        + (of_substance::template unit_traits<UnitsA::u_substance::value>::value_as_long
            * Abstract_pq::pwr_substance)
        + (of_intensity::template unit_traits<UnitsA::u_intensity::value>::value_as_long
            * Abstract_pq::pwr_intensity)
        + of_quantity::template mx_traits<Q_mxA>::value_as_long ;  

        static long const   scaleB
        = (of_length::template unit_traits<UnitsB::u_length::value>::value_as_long
            * Abstract_pq::pwr_length)
        + (of_time::template unit_traits<UnitsB::u_time::value>::value_as_long 
            * Abstract_pq::pwr_time) 
        + (of_mass::template unit_traits<UnitsB::u_mass::value>::value_as_long
            * Abstract_pq::pwr_mass)
        +(of_temperature::template unit_traits<UnitsB::u_temperature::value>::value_as_long
            * Abstract_pq::pwr_temperature)
        + (of_current::template unit_traits<UnitsB::u_current::value>::value_as_long
            * Abstract_pq::pwr_current)
        + (of_substance::template unit_traits<UnitsB::u_substance::value>::value_as_long
            * Abstract_pq::pwr_substance)
        +(of_intensity::template unit_traits<UnitsB::u_intensity::value>::value_as_long
            * Abstract_pq::pwr_intensity)
        + of_quantity::template mx_traits<Q_mxB>::value_as_long ; 

        static bool const A_is_finer = (scaleA <= scaleB);

        // derive units of return type
#ifdef PHYSICAL_QUANTITIES_NO_BOOST_LIBRARY
        typedef typename if_c
#else
       typedef typename boost::mpl::if_c
#endif      
        <
            A_is_finer,
            UnitsA,
            UnitsB
        >::type units_type;
#ifdef PHYSICAL_QUANTITIES_NO_BOOST_LIBRARY
        typedef typename if_c
#else
       typedef typename boost::mpl::if_c
#endif     
        < 
            (Q_mxA == Q_mxB),
            typename of_quantity::template mx_traits<Q_mxA>::type,
            typename of_quantity::template mx_traits<of_quantity::null>::type
        >::type  Q_mx_type;

        // determine the Value_type of return type
        typedef  typename math_promote
        < 
            Value_typeA,Value_typeB
        >::type           value_type;
   
        // return type
        typedef p_quantity
        <
            Abstract_pq,
            value_type,
            units_type,
            Q_mx_type::value
        > return_type;
    };
    // truncated add subtract for shorter signature
    // on type
    template
    <
        typename Abstract_pq,
        typename Value_typeA,
        typename UnitsA,
        quantity_mx Q_mxA,
        typename Value_typeB,
        typename UnitsB,
        quantity_mx Q_mxB
    >
    struct pq_add_semantics : pq_base_add_semantics
    <
        Abstract_pq,
        Value_typeA,
        UnitsA,
        Q_mxA,
        Value_typeB,
        UnitsB,
        Q_mxB
    >{};
}//namespace physical_quantities
#endif
