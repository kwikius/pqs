// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//comp.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITY_CLASS_TEMPLATE_COMP_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITY_CLASS_TEMPLATE_COMP_HPP_INCLUDED2911030401

#include "../generic.hpp"

namespace physical_quantities{

    // compare(pqa,pqb) works like strcmp and string::compare:
    // if( a == b ) return 0;
    // if( a > b ) return 1;
    // if( a < b ) return -1;

    // compare is basis of all other comp functions

    //specialisation for same units, diff value_type
       template
        <
            typename Abstract_pq,
            typename Value_typeA,
            typename Value_typeB,
            typename Units,
            quantity_mx Q_mx
        > inline int
        compare
            (p_quantity
            < 
                Abstract_pq,
                Value_typeA,
                Units,
                Q_mx
            >const & a,
            p_quantity
            <
                Abstract_pq,
                Value_typeB,
                Units,
                Q_mx
            >const& b)
        {
//std::cout <<"in cmp\n";
            return (a() > b())? 1 :((a() < b())? -1 : 0);
        }
        

    template
    <
        typename Abstract_pq,
        typename Value_typeA,
        typename UnitsA,
        quantity_mx Q_mxA,

        typename Abstract_pq1,
        typename Value_typeB,
        typename UnitsB,
        quantity_mx Q_mxB
    >
    inline int
        compare
            (p_quantity
            < 
                Abstract_pq,
                Value_typeA,
                UnitsA,
                Q_mxA
            >const & a,
            p_quantity
            <
                Abstract_pq1,
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
                    Abstract_pq1
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
            // scale each to others units
            // and see if they touch or cross in the process
            // must scale all to the dub version...

             p_quantity
             <
                Abstract_pq,
                Value_typeA,
                UnitsA,
                Q_mxA
             > ta(a);

             p_quantity
             <
                Abstract_pq,
                Value_typeA,
                UnitsA,
                Q_mxA
             > bDash(b);

             p_quantity
             <
                Abstract_pq,
                Value_typeB,
                UnitsB,
                Q_mxB
             > tb(b);

              p_quantity
              <
                Abstract_pq,
                Value_typeB,
                UnitsB,
                Q_mxB
              > aDash(a);

              if ( (ta() == bDash()) 
                    || (tb() == aDash()) ){
                  return 0;
              }
              if (ta() > bDash() ){
                  return ( tb() > aDash() )? 0 : 1;
              }
              return (aDash() > tb() )? 0:-1;
        }

    // PQa == PQb
    template
    <
        typename Abstract_pq,
        typename Value_typeA,
        typename UnitsA,
        quantity_mx Q_mxA,

        typename Abstract_pq1,
        typename Value_typeB,
        typename UnitsB,
        quantity_mx Q_mxB
    >
    inline bool
        operator ==
            (p_quantity
            <
                Abstract_pq,
                Value_typeA,
                UnitsA,
                Q_mxA
            >const & a,
            p_quantity
            <
                Abstract_pq1,
                Value_typeB,
                UnitsB,
                Q_mxB
            >const& b)
        {
           return (compare(a,b) == 0);
        }
        //pqA !=pqB
    template
    <
        typename Abstract_pq,
        typename Value_typeA,
        typename UnitsA,
        quantity_mx Q_mxA,
        typename Abstract_pq1,
        typename Value_typeB,
        typename UnitsB,
        quantity_mx Q_mxB
    >
    inline bool
        operator !=
            (p_quantity
            <
                Abstract_pq,
                Value_typeA,
                UnitsA,
                Q_mxA
            >const & a,
            p_quantity
            <
                Abstract_pq1,
                Value_typeB,
                UnitsB,
                Q_mxB
            >const& b)
        {
           return (compare(a,b) != 0);
        }
 // PQa < PQb
    template
    <
        typename Abstract_pq,
        typename Value_typeA,
        typename UnitsA,
        quantity_mx Q_mxA,
        typename Abstract_pq1,
        typename Value_typeB,
        typename UnitsB,
        quantity_mx Q_mxB
    >
    inline bool
        operator <
            (p_quantity
            <
                Abstract_pq,
                Value_typeA,
                UnitsA,
                Q_mxA
            >const & a,
            p_quantity
            <
                Abstract_pq1,
                Value_typeB,
                UnitsB,
                Q_mxB
            >const& b)
            {
                return (compare(a,b) < 0);
            }
    template
    <
        typename Abstract_pq,
        typename Value_typeA,
        typename UnitsA,
        quantity_mx Q_mxA,
        typename Abstract_pq1,
        typename Value_typeB,
        typename UnitsB,
        quantity_mx Q_mxB
    >
    inline bool
        operator >
            (p_quantity
            <
                Abstract_pq,
                Value_typeA,
                UnitsA,
                Q_mxA
            >const & a,
            p_quantity
            <
                Abstract_pq1,
                Value_typeB,
                UnitsB,
                Q_mxB
            >const& b)
            {
                return (compare(a,b) > 0);
            }

    template
    <
        typename Abstract_pq,
        typename Value_typeA,
        typename UnitsA,
        quantity_mx Q_mxA,
        typename Abstract_pq1,
        typename Value_typeB,
        typename UnitsB,
        quantity_mx Q_mxB
    >
    inline bool
        operator <=
            (p_quantity
            <
                Abstract_pq,
                Value_typeA,
                UnitsA,
                Q_mxA
            >const & a,
             p_quantity
             <
                Abstract_pq1,
                Value_typeB,
                UnitsB,
                Q_mxB
             >const& b)
            {
                return (compare(a,b) <= 0);
            }
    template
    <
        typename Abstract_pq,
        typename Value_typeA,
        typename UnitsA,
        quantity_mx Q_mxA,
        typename Abstract_pq1,
        typename Value_typeB,
        typename UnitsB,
        quantity_mx Q_mxB>
    inline bool
        operator >=
            (p_quantity
            <
                Abstract_pq,
                Value_typeA,
                UnitsA,
                Q_mxA
            >const & a,
            p_quantity
            <
                Abstract_pq1,
                Value_typeB,
                UnitsB,
                Q_mxB
            >const& b )
            {
                return (compare(a,b) >= 0);
            }
}//namespace physical_quantities

#endif
