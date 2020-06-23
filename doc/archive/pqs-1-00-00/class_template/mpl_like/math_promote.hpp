// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//math_promote.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.
//revision
// 17 10 03

#ifndef PHYSICAL_QUANTITIES_MATH_PROMOTE_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITIES_MATH_PROMOTE_HPP_INCLUDED2911030401

#include "boost_lib_dependencies.hpp"
#ifdef PHYSICAL_QUANTITIES_NO_BOOST_LIBRARY
#include "if.hpp"
#include "is_arithmetic.hpp"
#else
#include "boost/type_traits/is_arithmetic.hpp"
#include "boost/mpl/if.hpp"
#endif
#include "arithmetic_promotion.hpp"

namespace physical_quantities{

    template <bool,typename A, typename B>
    class promote_arithmetic;

    template <typename A, typename B>
    class promote_arithmetic<true,A,B>{
    public:
#ifdef PHYSICAL_QUANTITIES_NO_BOOST_LIBRARY
        typedef typename if_c< ( arithmetic_promotion<A>::value >=
#else
        typedef typename ::boost::mpl::if_c< ( arithmetic_promotion<A>::value >=
#endif
        arithmetic_promotion<B>::value ),A,B >::type type;
    };

    //non arithmetic promotion...?
    template <typename A, typename B>
    class promote_arithmetic<false,A,B>{
    public:
        //typedef long double type;
        typedef void type;
    };

    template <typename A, typename B>
    class math_promote{
    public:
#ifdef PHYSICAL_QUANTITIES_NO_BOOST_LIBRARY
        typedef typename promote_arithmetic<( is_arithmetic<A>::value &&
                                is_arithmetic<B>::value),A,B >::type type;
#else
        typedef typename promote_arithmetic<( ::boost::is_arithmetic<A>::value &&
                        ::boost::is_arithmetic<B>::value),A,B >::type type;
#endif                             
    };
}
#endif

