// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//units_of_time.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITIES_UNITS_OF_TIME_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITIES_UNITS_OF_TIME_HPP_INCLUDED2911030401

#include "dimension_unit_classes.hpp"

namespace physical_quantities{
  
    struct of_time : dimension::of_dimension<dimension::Time>{

        enum unit
        {
            ps      =   -12000000,
            ns      =    -9000000,
            us      =    -6000000,
            ms      =    -3000000,
            null    =           0,
            s       =           0,
            min     =     1778151,
            h       =     3556303,
            d       =     4936514,
            weeks   =     5781612
        };

        template< unit u>
        struct unit_traits : base_unit_traits<unit,u>{
            inline static float  number_of_std_units_in();
            inline static const char*const c_str();
        };
    } ;
    //ps
    template<>
    inline float of_time::unit_traits<of_time::ps>::number_of_std_units_in()
    {return 1e-12f;}  
    template<>
    inline char const*const of_time::unit_traits<of_time::ps>::c_str()
    {return "ps";}
    //ns
    template<>
    inline float of_time::unit_traits<of_time::ns>::number_of_std_units_in()
    {return 1e-9f;}  
    template<>
    inline char const*const of_time::unit_traits<of_time::ns>::c_str()
    {return "ns";}
    //us
    template<>
    inline float of_time::unit_traits<of_time::us>::number_of_std_units_in()
    {return 1e-6f;}
    template<>
    inline char const*const of_time::unit_traits<of_time::us>::c_str()
    {return "us";}
    //ms
    template<>
    inline float of_time::unit_traits<of_time::ms>::number_of_std_units_in()
    {return 1e-3f;}
    template<>
    inline char const*const of_time::unit_traits<of_time::ms>::c_str()
    {return "ms";}
    //s
    template<>
    inline float of_time::unit_traits<of_time::s>::number_of_std_units_in()
    {return 1.0f;}
    template<>
    inline char const*const of_time::unit_traits<of_time::s>::c_str()
    {return "s";}
    //min
    template<>
    inline float of_time::unit_traits<of_time::min>::number_of_std_units_in()
    {return 60.0f;}
    template<>
    inline char const*const of_time::unit_traits<of_time::min>::c_str()
    {return "min";}
    //h
    template<>
    inline float of_time::unit_traits<of_time::h>::number_of_std_units_in()
    {return 3600.0f;}
    template<>
    inline   char const*const    of_time::unit_traits<of_time::h>::c_str()
    {return "h";}
    //d
    template<>
    inline float of_time::unit_traits<of_time::d>::number_of_std_units_in()
    {return 86400.0f;}
    template<>
    inline   char const*const    of_time::unit_traits<of_time::d>::c_str()
    {return "d";}
    template<>
    inline float of_time::unit_traits<of_time::weeks>::number_of_std_units_in()
    {return 604800.0f;}
    template<>
    inline   char const*const    of_time::unit_traits<of_time::weeks>::c_str()
    {return "weeks";}


}//physical_quantities

#endif

