// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
// concept_checking.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.


#ifndef PHYSICAL_QUANTITIES_CONCEPT_CHECKING_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITIES_CONCEPT_CHECKING_HPP_INCLUDED2911030401

#include "mpl_like/boost_lib_dependencies.hpp"
#ifdef PHYSICAL_QUANTITIES_NO_BOOST_LIBRARY
#include "mpl_like/if.hpp"
#else 
#include "boost/mpl/if.hpp"
#endif
#include "interface/interface.hpp"

namespace physical_quantities{

    // Causes a compiler error when an attempt is made to
    // initialise a p_quantity
    // by a non-dimensionally-equivalent physical-quantity
    template <typename AbstractPQa,typename AbstractPQb>
    inline void DimensionallyEquivalentConcept()
    {
    // Concept fails if AbstractPQb is not dimensionally equivalent to AbstractPQa
        AbstractPQb dimensionally_equivalent_pq;
        AbstractPQa pq = dimensionally_equivalent_pq;
        pq = pq;
    // Look for a reference to your source code position
    // in the compiler error message.
    }

    template
    <
        typename UnitsA,
        quantity_mx Q_mxA,
        typename UnitsB,
        quantity_mx Q_mxB
    >
    struct UnitConversionWarningConceptStruct{
        typedef float from_type;
#ifdef PHYSICAL_QUANTITIES_NO_BOOST_LIBRARY
        typedef typename if_c<(
#else 
        typedef typename boost::mpl::if_c<(
#endif
      
        (UnitsA::u_length::value_as_long == UnitsB::u_length::value_as_long) &&
        (UnitsA::u_time::value_as_long == UnitsB::u_time::value_as_long) &&
        (UnitsA::u_mass::value_as_long == UnitsB::u_mass::value_as_long) &&
        (UnitsA::u_temperature::value_as_long == UnitsB::u_temperature::value_as_long) &&
        (UnitsA::u_current::value_as_long == UnitsB::u_current::value_as_long) &&
        (UnitsA::u_substance::value_as_long == UnitsB::u_substance::value_as_long) &&
        (UnitsA::u_intensity::value_as_long == UnitsB::u_intensity::value_as_long) &&
        (Q_mxA == Q_mxB)
         ),from_type,int>::type to_type;
    };

    template
    <
        typename UnitsA,
        quantity_mx Q_mxA,
        typename UnitsB,
        quantity_mx Q_mxB
    >
    inline void  UnitConversionWarningConcept()
    {
      typename UnitConversionWarningConceptStruct
        <
            UnitsA,
            Q_mxA,
            UnitsB,
            Q_mxB
        >::from_type val = 0.99f;
       typename UnitConversionWarningConceptStruct
        <
            UnitsA,
            Q_mxA,
            UnitsB,
            Q_mxB
        >::to_type t = val;
       t=t;
    }

}//namespace physical_quantities

#endif

