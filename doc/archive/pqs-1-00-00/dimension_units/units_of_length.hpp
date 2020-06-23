// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
// units_of_length.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITIES_UNITS_OF_LENGTH_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITIES_UNITS_OF_LENGTH_HPP_INCLUDED2911030401

#include "dimension_unit_classes.hpp"

namespace physical_quantities{
 
    struct of_length : dimension::of_dimension<dimension::Length>{ 
        enum unit
        {
            nm          =    -9000000,
            um          =    -6000000,
            mm          =    -3000000,
            cm          =    -2000000,
            dm          =    -1000000,
            in          =    -1595166,
            ft          =     -515985,
            yd          =      -38864,
            null        =           0,          // alias for std unit
            m           =           0,          //standard unit
            km          =     3000000,
            mi          =     3206649,
            AU          =    11174925,
            l_y_        =    15975925,
            pc          =    16489351
        };
        template< unit u>
        struct unit_traits : base_unit_traits<unit,u>{
            static inline float  number_of_std_units_in();
            static inline const char*const c_str();
        };
    } ;
    //nm
    template<>
    inline float of_length::unit_traits<of_length::nm>::number_of_std_units_in()
    { return 1e-9f;}
    template<>
    inline char const*const of_length::unit_traits<of_length::nm>::c_str()
    {return "nm";}
    //um
    template<>
    inline float of_length::unit_traits<of_length::um>::number_of_std_units_in()
    { return 1e-6f;}
    template<>
    inline char const*const of_length::unit_traits<of_length::um>::c_str()
    {return "um";}
    //mm
    template<>
    inline float of_length::unit_traits<of_length::mm>::number_of_std_units_in()
    { return 1e-3f;}
    template<>
    inline char const*const of_length::unit_traits<of_length::mm>::c_str()
    {return "mm";}
    //cm 
    template<>
    inline float of_length::unit_traits<of_length::cm>::number_of_std_units_in()
    { return 1e-2f;}
    template<>
    inline char const*const of_length::unit_traits<of_length::cm>::c_str()
    {return "cm";}
    //in
    template<>
    inline float of_length::unit_traits<of_length::in>::number_of_std_units_in()
    { return 2.54e-2f;}
    template<>
    inline char const*const of_length::unit_traits<of_length::in>::c_str()
    {return "in";}
    //dm 
    template<>
    inline float of_length::unit_traits<of_length::dm>::number_of_std_units_in()
    { return 1e-1f;}
    template<>
    inline char const*const of_length::unit_traits<of_length::dm>::c_str()
    {return "dm";}
    //ft
    template<>
    inline float of_length::unit_traits<of_length::ft>::number_of_std_units_in()
    {return 0.3048f;}
    template<>
    inline char const*const of_length::unit_traits<of_length::ft>::c_str()
    {return "ft";}
    //yd
    template<>
    inline float of_length::unit_traits<of_length::yd>::number_of_std_units_in()
    {return 0.9144f;}
    template<>
    inline char const*const of_length::unit_traits<of_length::yd>::c_str()
    {return "yd";}
    //m
    template<>
    inline float of_length::unit_traits<of_length::m>::number_of_std_units_in()
    {return 1.0f;}
    template<>
    inline char const*const of_length::unit_traits<of_length::m>::c_str()
    {return "m";}
    //km
    template<>
    inline float of_length::unit_traits<of_length::km>::number_of_std_units_in()
    {return 1e+3f;}
    template<>
    inline char const*const of_length::unit_traits<of_length::km>::c_str()
    {return "km";}
    //mi
    template<>
    inline  float   of_length::unit_traits<of_length::mi>::number_of_std_units_in()
    {return 1.609344e+3f;}
    template<>
    inline  char const*const of_length::unit_traits<of_length::mi>::c_str()
    {return "mi";}
    //AU
    template<>
        inline  float   of_length::unit_traits<of_length::AU>::number_of_std_units_in()
    {return 1.495979e11f;}
    template<>
        inline  char const*const of_length::unit_traits<of_length::AU>::c_str()
    {return "AU";}

    //light year
    template<>
    inline  float   of_length::unit_traits<of_length::l_y_>::number_of_std_units_in()
    {return 9.46073e15f;}
    template<>
    inline  char const*const    of_length::unit_traits<of_length::l_y_>::c_str()
    {return "light-years";}
    //parsec
    template<>
    inline  float   of_length::unit_traits<of_length::pc>::number_of_std_units_in()
    {return 3.085678e16f;}
    template<>
    inline  char const*const    of_length::unit_traits<of_length::pc>::c_str()
    {return "pc";}
}//physical_quantities
#endif
