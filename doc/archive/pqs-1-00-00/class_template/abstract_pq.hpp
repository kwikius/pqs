// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//abstract_pq.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.
//
//Revision

// abstract physical quantity class template param

#ifndef  PHYSICAL_QUANTITIES_ABSTRACT_PQ_HPP_INCLUDED2911030401
#define  PHYSICAL_QUANTITIES_ABSTRACT_PQ_HPP_INCLUDED2911030401

namespace physical_quantities{
//sequence
//Length,Time,Mass,Temperature,Current,Substance,Intensity
    template
    <
        int P_len  ,
        int P_time=0,
        int P_mass=0,
        int P_temp=0,
        int P_current=0,
        int P_substance =0,
        int P_intensity=0
    >
    struct abstract_pq{
        static int const pwr_length = P_len;
        static int const pwr_time = P_time;
        static int const pwr_mass = P_mass;
        static int const pwr_temperature = P_temp;
        static int const pwr_current = P_current;
        static int const pwr_substance = P_substance;
        static int const pwr_intensity = P_intensity;
    };
    template <typename A, typename B>
    struct pq_add_powers_for_multiply{
       typedef abstract_pq
       <
            A::pwr_length + B::pwr_length,
            A::pwr_time + B::pwr_time,
            A::pwr_mass + B::pwr_mass,
            A::pwr_temperature + B::pwr_temperature,
            A::pwr_current + B::pwr_current,
            A::pwr_substance + B::pwr_substance,
            A::pwr_intensity + B::pwr_intensity
        >  type;
    };
    template <typename A, typename B>
    struct pq_subtract_powers_for_divide{
       typedef abstract_pq
       <
            A::pwr_length - B::pwr_length,
            A::pwr_time - B::pwr_time,
            A::pwr_mass - B::pwr_mass,
            A::pwr_temperature - B::pwr_temperature,
            A::pwr_current - B::pwr_current,
            A::pwr_substance - B::pwr_substance,
            A::pwr_intensity - B::pwr_intensity
        >  type;
    };
    template <typename A>
    struct pq_negate_powers_for_divide_by{
       typedef abstract_pq
       <
            (-(A::pwr_length)),
            (-(A::pwr_time)),
            (-(A::pwr_mass)),
            (-(A::pwr_temperature)),
            (-(A::pwr_current)),
            (-(A::pwr_substance)),
            (-(A::pwr_intensity))
        >  type;
    };

    template <typename Abstract_pq, int Power>
    struct pq_multiply_power_for_exp{
       typedef abstract_pq
       <
            ((Abstract_pq::pwr_length) * Power),
            ((Abstract_pq::pwr_time) * Power),
            ((Abstract_pq::pwr_mass) * Power),
            ((Abstract_pq::pwr_temperature) * Power),
            ((Abstract_pq::pwr_current) * Power),
            ((Abstract_pq::pwr_substance) * Power),
            ((Abstract_pq::pwr_intensity) * Power)
        >  type;
    };

    template <typename A, int B>
    struct pq_divide_power_for_exp{
       typedef abstract_pq
       <
            ((A::pwr_length) / B),
            ((A::pwr_time) / B),
            ((A::pwr_mass) / B),
            ((A::pwr_temperature) / B),
            ((A::pwr_current) / B),
            ((A::pwr_substance) / B),
            ((A::pwr_intensity) / B)
        >  type;
    };
    template <typename A, int B>
    struct pq_divide_power_with_remainder_for_exp{
       typedef abstract_pq
       <
            (((A::pwr_length) / B) + ((A::pwr_length) % B)),
            (((A::pwr_time) / B) + ((A::pwr_time) % B)),
            (((A::pwr_mass) / B) + ((A::pwr_mass) % B)),
            (((A::pwr_temperature) / B) + ((A::pwr_temperature) % B)),
            (((A::pwr_current) / B) + ((A::pwr_current) % B)),
            (((A::pwr_substance) / B) + ((A::pwr_substance) % B)),
            (((A::pwr_intensity) / B) + ((A::pwr_intensity) % B))
        >  type;
    };
}
#endif
