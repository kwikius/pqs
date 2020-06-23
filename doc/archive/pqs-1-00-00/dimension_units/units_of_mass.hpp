// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
// units_of_mass.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITIES_UNITS_OF_MASS_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITIES_UNITS_OF_MASS_HPP_INCLUDED2911030401

#include "dimension_unit_classes.hpp"

namespace physical_quantities{
    
    // container for dimension of time units
    struct of_mass : dimension::of_dimension<dimension::Mass>{

        enum unit
        { 
            ug      =  -9000000,
            mg      =  -6000000,
            g       =  -3000000,
            oz      =  -1547454,
            lb      =   -343334,
            null    =         0,
            kg      =         0,
            t       =   3000000
        };
        template< unit u>
        struct unit_traits : base_unit_traits<unit,u>{
            static inline float number_of_std_units_in();
            static inline const char*const c_str();
        };
    } ;
    //ug
    template<>
    inline float of_mass::unit_traits<of_mass::ug>::number_of_std_units_in()
                        {return 1e-9f;}
    template<>
    inline char const*const of_mass::unit_traits<of_mass::ug>::c_str()
                        {return "ug";}
    //mg
    template<>
    inline float of_mass::unit_traits<of_mass::mg>::number_of_std_units_in()
                        {return 1e-6f;}
    template<>
    inline char const*const of_mass::unit_traits<of_mass::mg>::c_str()
                        {return "mg";}
    //g
    template<>
    inline float of_mass::unit_traits<of_mass::g>::number_of_std_units_in()
                        {return 1e-3f;}
    template<>
    inline char const*const of_mass::unit_traits<of_mass::g>::c_str()
                        {return "g";}
     //oz
    template<>
    inline float of_mass::unit_traits<of_mass::oz>::number_of_std_units_in()
                        {return 2.834952e-2f;}
    template<>
    inline char const*const of_mass::unit_traits<of_mass::oz>::c_str()
                        {return "oz";}
    
    //pounds
    template<>
    inline float of_mass::unit_traits<of_mass::lb>::number_of_std_units_in()
                        {return 0.4535924f;}
    template<>
    inline char const*const of_mass::unit_traits<of_mass::lb>::c_str()
                        {return "lb";}
    //kg
    template<>
    inline float of_mass::unit_traits<of_mass::kg>::number_of_std_units_in()
                        {return 1.0f;}
    template<>
    inline char const*const of_mass::unit_traits<of_mass::kg>::c_str()
                        {return "kg";}
    //tonne/metric ton
    template<>
    inline float of_mass::unit_traits<of_mass::t>::number_of_std_units_in()
                        {return 1e3f;}
    template<>
    inline char const*const of_mass::unit_traits<of_mass::t>::c_str()
                        {return "t";}
}//physical_quantities

#endif

