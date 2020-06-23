// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
// of_quantity.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITIES_OF_QUANTITY_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITIES_OF_QUANTITY_HPP_INCLUDED2911030401

#include "../class_template/interface/multiplied_log_enum.hpp"

namespace physical_quantities{

    struct of_quantity {
       
        enum mx_id{
             mx_1e_minus15     = -15000000,
             mx_1e_minus14     = -14000000,
             mx_1e_minus13     = -13000000,
             mx_1e_minus12     = -12000000,
             mx_1e_minus11     = -11000000,
             mx_1e_minus10     = -10000000,
             mx_1e_minus9      =  -9000000,
             mx_1e_minus8      =  -8000000,
             erg_to_J          =  -7000000,
             mx_1e_minus7      =  -7000000,
             mx_1e_minus6      =  -6000000,
             dyne_to_N         =  -5000000,
             mx_1e_minus5      =  -5000000,
             mx_1e_minus4      =  -4000000,
             mx_1e_minus3      =  -3000000,
             mx_1e_minus2      =  -2000000,
             mx_1e_minus1      =  -1000000,
             null              =         0,
             us_gallon_to_L    =    578113,
             lbf_to_N          =    648186,
             imp_gallon_to_L   =    657638,
             kgf_to_N          =    991521,
             mx_1e1            =   1000000,
             mx_1e2            =   2000000,
             kN_to_N           =   3000000,
             mx_1e3            =   3000000,
             psi_to_Pa         =   3838519,
             mx_1e4            =   4000000,
             mx_1e5            =   5000000,
             mx_1e6            =   6000000,
             mx_1e9            =   9000000,
             mx_1e12           =  12000000
        };

        template<mx_id id>
        struct mx_traits : multiplied_log_enum<mx_id,id>{
            inline static float  number_of_dub_in();
        };
     }; //of_quantity

    //1e-15
    template<>
        inline float of_quantity::mx_traits<of_quantity::mx_1e_minus15>::number_of_dub_in()
    {return 1e-15f;}
    //1e-14
    template<>
        inline float of_quantity::mx_traits<of_quantity::mx_1e_minus14>::number_of_dub_in()
    {return 1e-14f;}
    //1e-13
    template<>
        inline float of_quantity::mx_traits<of_quantity::mx_1e_minus13>::number_of_dub_in()
    {return 1e-13f;}
   //1e-12
    template<>
        inline float of_quantity::mx_traits<of_quantity::mx_1e_minus12>::number_of_dub_in()
    {return 1e-12f;}
    //1e-11
    template<>
        inline float of_quantity::mx_traits<of_quantity::mx_1e_minus11>::number_of_dub_in()
    {return 1e-11f;}
    //1e-10
    template<>
        inline float of_quantity::mx_traits<of_quantity::mx_1e_minus10>::number_of_dub_in()
    {return 1e-10f;}
    //1e-9
    template<>
        inline float of_quantity::mx_traits<of_quantity::mx_1e_minus9>::number_of_dub_in()
    {return 1e-9f;}
    //1e-8
    template<>
        inline float of_quantity::mx_traits<of_quantity::mx_1e_minus8>::number_of_dub_in()
    {return 1e-8f;}
    //1e-7
    template<>
        inline float of_quantity::mx_traits<of_quantity::mx_1e_minus7>::number_of_dub_in()
    {return 1e-7f;}
    //1e-6
    template<>
        inline float of_quantity::mx_traits<of_quantity::mx_1e_minus6>::number_of_dub_in()
    {return 1e-6f;}
    //1e-5
    template<>
        inline float of_quantity::mx_traits<of_quantity::mx_1e_minus5>::number_of_dub_in()
    {return 1e-5f;}
    //1e-4
    template<>
        inline float of_quantity::mx_traits<of_quantity::mx_1e_minus4>::number_of_dub_in()
    {return 1e-4f;}
    //1e-3
    template<>
        inline float of_quantity::mx_traits<of_quantity::mx_1e_minus3>::number_of_dub_in()
    {return 1e-3f;}
    //1e-2
    template<>
        inline float of_quantity::mx_traits<of_quantity::mx_1e_minus2>::number_of_dub_in()
    {return 1e-2f;}
    //1e-1
    template<>
        inline float of_quantity::mx_traits<of_quantity::mx_1e_minus1>::number_of_dub_in()
    {return 1e-1f;}
     //null
    template<>
    inline float of_quantity::mx_traits<of_quantity::null>::number_of_dub_in()
    {return 1.0f;}
     //US gallon to L
    template<>
    inline float of_quantity::mx_traits<of_quantity::us_gallon_to_L>::number_of_dub_in()
    {return 3.785412f;}
    //lbf to N
    template<>
    inline float of_quantity::mx_traits<of_quantity::lbf_to_N>::number_of_dub_in()
    {return 4.448222f;}
    //imp gallon to L
    template<>
    inline float of_quantity::mx_traits<of_quantity::imp_gallon_to_L>::number_of_dub_in()
    {return 4.54609f;}
    //kgf to N
    template<>
    inline float of_quantity::mx_traits<of_quantity::kgf_to_N>::number_of_dub_in()
    {return 9.80665f;}
    //1e1
    template<>
    inline float of_quantity::mx_traits<of_quantity::mx_1e1>::number_of_dub_in()
    {return 1e1f;}
    //1e2
    template<>
    inline float of_quantity::mx_traits<of_quantity::mx_1e2>::number_of_dub_in()
    {return 1e2f;}
    //1e3
    template<>
    inline float of_quantity::mx_traits<of_quantity::mx_1e3>::number_of_dub_in()
    {return 1e3f;}
    //psi to Pa 
    template<>
    inline float of_quantity::mx_traits<of_quantity::psi_to_Pa>::number_of_dub_in()
    {return 6.894757e3f;}
    //1e4
    template<>
    inline float of_quantity::mx_traits<of_quantity::mx_1e4>::number_of_dub_in()
    {return 1e4f;}
    //1e5
    template<>
    inline float of_quantity::mx_traits<of_quantity::mx_1e5>::number_of_dub_in()
    {return 1e5f;}
    //1e6
    template<>
    inline float of_quantity::mx_traits<of_quantity::mx_1e6>::number_of_dub_in()
    {return 1e6f;}
     //1e9
    template<>
    inline float of_quantity::mx_traits<of_quantity::mx_1e9>::number_of_dub_in()
    {return 1e9f;}
     //1e12
    template<>
    inline float of_quantity::mx_traits<of_quantity::mx_1e12>::number_of_dub_in()
    {return 1e12f;}
 
}

#endif
