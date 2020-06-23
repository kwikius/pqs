// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//units_ostream.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITY_CLASS_TEMPLATE_UNITS_OSTREAM_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITY_CLASS_TEMPLATE_UNITS_OSTREAM_HPP_INCLUDED2911030401

#include <iostream>
#include "../class_template/units_out.hpp"
#include "../class_template/interface/interface.hpp"

namespace physical_quantities{

            //This function picks up the 
            //physical_quantity_dub_units_out class
            //thrown out by pq.units() 
           
            // The general idea is to use the p.units() form for
            // output of the dub units (and any scalieng)
            // the units(pq) form is meant for overloading.
            // hence eg for a kilograms-force pq
            //pq.units() gives  "kg.m.s-2 * 9.8XX"
            //units(pq) gives   "kgf"

    template
    <
        typename Abstract_pq,
        typename Units,
        quantity_mx Q_mx
    >
    inline std::ostream& 
        operator << 
            (std::ostream& os,
                physical_quantity_dub_units_out
                < 
                    Abstract_pq,
                    Units,
                    Q_mx
                > const&  )

        {
            int P_mass = Abstract_pq::pwr_mass;
            int P_time = Abstract_pq::pwr_time;
            int P_len = Abstract_pq::pwr_length;
            int P_temp = Abstract_pq::pwr_temperature;
            int P_current = Abstract_pq::pwr_current;
            int P_substance = Abstract_pq::pwr_substance;
            int P_intensity = Abstract_pq::pwr_intensity;

            (Q_mx)
                ? os << '['
                : os << "";
            if (P_mass){
                os << of_mass::unit_traits<Units::u_mass::value>::c_str();
                if( P_mass != 1){
                    if (P_mass > 1)
                        os << '+';
                    os << P_mass;
                }
                if (P_len ||P_time || P_temp ||P_current ||P_substance || P_intensity)
                    os <<'.';
            }
            if (P_len) {
                os << of_length::unit_traits<Units::u_length::value>::c_str();
                if(P_len !=1){
                    if (P_len > 1)
                        os << '+';
                    os <<P_len;
                }
                if (P_time || P_temp ||P_current ||P_substance || P_intensity)
                    os << '.';
            }
            if (P_time){
                os << of_time::unit_traits<Units::u_time::value>::c_str();
                if( P_time !=1){
                    if (P_time > 1)
                        os << '+';
                    os << P_time;
                }
                if ( P_temp ||P_current ||P_substance || P_intensity)
                    os << '.';
            }
            if (P_temp){
                os << of_temperature::unit_traits<Units::u_temperature::value>::c_str();
                if( P_temp !=1){
                    if (P_temp > 1)
                        os << '+';
                    os << P_temp;
                }
                if ( P_current ||P_substance || P_intensity)
                    os << '.';
            }
            if (P_current){
                os << of_current::unit_traits<Units::u_current::value>::c_str();
                if( P_current !=1){
                    if (P_current > 1)
                        os << '+';
                    os << P_current;
                }
                 if ( P_substance || P_intensity)
                    os << '.';
            }
            if (P_substance){
                os << of_substance::unit_traits<Units::u_substance::value>::c_str();
                if( P_substance !=1){
                    if (P_substance > 1)
                        os << '+';
                    os << P_substance;
                }
                 if (P_intensity)
                    os << '.';
            }
            if (P_intensity){
                os << of_intensity::unit_traits<Units::u_intensity::value>::c_str();
                if( P_intensity !=1){
                    if (P_intensity > 1)
                        os << '+';
                    os << P_intensity;
                }
            }
            (Q_mx )
             ? os << " * " 
                << of_quantity::mx_traits<Q_mx>::number_of_dub_in() 
                << ']'
             : os << "";

            return os;
        }
}

#endif

