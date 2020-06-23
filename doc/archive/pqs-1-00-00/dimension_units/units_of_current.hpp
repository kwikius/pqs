// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
// units_of_current.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITIES_UNITS_OF_CURRENT_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITIES_UNITS_OF_CURRENT_HPP_INCLUDED2911030401

#include "dimension_unit_classes.hpp"

namespace physical_quantities{
    
    // container for dimension of time units
    struct of_current : dimension::of_dimension<dimension::Current>{

        enum unit
        { 
            pA          =      -12000000,
            nA          =       -9000000,
            uA          =       -6000000,
            mA          =       -3000000,
            null        =              0,
            A           =              0,
            abampere    =        1000000
        };
        template< unit u>
        struct unit_traits : base_unit_traits<unit,u>{
            static inline float number_of_std_units_in();
            static inline const char*const c_str();
        };
    } ;

    //pA
    template<>
    inline float of_current::unit_traits<of_current::pA>::number_of_std_units_in()
    {return 1e-12f;}
    template<>
    inline char const*const of_current::unit_traits<of_current::pA>::c_str()
    {return "pA";}
    //nA
    template<>
    inline float of_current::unit_traits<of_current::nA>::number_of_std_units_in()
    {return 1e-9f;}
    template<>
    inline char const*const of_current::unit_traits<of_current::nA>::c_str()
    {return "nA";}
    //uA
    template<>
    inline float of_current::unit_traits<of_current::uA>::number_of_std_units_in()
    {return 1e-6f;}
    template<>
    inline char const*const of_current::unit_traits<of_current::uA>::c_str()
    {return "uA";}
    //mA
    template<>
    inline float of_current::unit_traits<of_current::mA>::number_of_std_units_in()
    {return 1e-3f;}
    template<>
    inline char const*const of_current::unit_traits<of_current::mA>::c_str()
    {return "mA";}
    //A
    template<>
    inline float of_current::unit_traits<of_current::A>::number_of_std_units_in()
    {return 1.0f;}
    template<>
    inline char const*const of_current::unit_traits<of_current::A>::c_str()
    {return "A";}
    //abampere
    template<>
    inline float of_current::unit_traits<of_current::abampere>::number_of_std_units_in()
    {return 10.0f;}
    template<>
    inline char const*const of_current::unit_traits<of_current::abampere>::c_str()
    {return "abampere";}

}//physical_quantities

#endif

