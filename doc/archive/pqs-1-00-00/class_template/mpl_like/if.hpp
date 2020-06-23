// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
// local version of if_c

// initially from C++ templates the complete guide by David Vandevvorde &  Nicolai M.Josuttis

// from boost::mpl::if_c by http://www.boost.org
// which is:

// Copyright (c) 2000-03 Boost.org
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.
//
// See http://www.boost.org/libs/mpl for documentation.
// http://www.boost.org/more/download.html

#ifndef PHYSICAL_QUANTITIES_IF_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITIES_IF_HPP_INCLUDED2911030401

namespace physical_quantities {

    template <bool If , typename value_typeA,typename value_typeB>
    class if_c{
    };

    template <typename value_typeA,typename value_typeB>
    class if_c<true,value_typeA,value_typeB>{
    public:
        typedef value_typeA  type;
    };
    template <typename value_typeA,typename value_typeB>
    class if_c<false,value_typeA,value_typeB>{
    public:
        typedef value_typeB  type;
    };
}
#endif



 
