// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//dimless.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITY_CLASS_TEMPLATE_DIMLESS_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITY_CLASS_TEMPLATE_DIMLESS_HPP_INCLUDED2911030401

#include <cmath>
#include "interface/interface.hpp"
#include "mpl_like/math_promote.hpp"
#include "abstract_pq.hpp"
   
namespace physical_quantities {

    // specialisation of a physical-quantity for 0,0,0 powers
    // implicit conversion to from Value_type
    // looks like a scalar.
    // never instantiated
    template
    <
        typename Value_type,
        typename Units
    > 
    class p_quantity
    <
        abstract_pq<0>,
        Value_type,
        Units,
        of_quantity::null
    > {
    private:
        Value_type m_value;
         p_quantity
        < 
            abstract_pq<0>,
            Value_type,
            Units,
            of_quantity::null
        >  ();
    public:
      
        typedef Value_type identity;

        template
        <
            typename Value_type1,
            typename Units1,
            quantity_mx Q_mx1
        >
        static inline typename math_promote
            <
                Value_type,
                Value_type1
            > ::type 
            scale_from(Value_type1 const& v)
            {
                typedef typename math_promote
                <
                    typename math_promote
                    <
                        Value_type,
                        Value_type1 
                    > ::type,
                    float 
                > ::type  calc_type;
                static calc_type
                     const scale 
                    = (of_quantity::template mx_traits<Q_mx1>::number_of_dub_in() 
                        / of_quantity::template mx_traits<of_quantity::null>::number_of_dub_in());
                return v * scale;
            }
    };//specialisation for 0,0,0 powers
//.....................................................
}// physical_quantities
#endif
