// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//aux_units_out.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITIES_STREAM_OUT_INCLUDED
#define PHYSICAL_QUANTITIES_STREAM_OUT_INCLUDED

#include <iostream>

#include "../class_template/interface/interface.hpp"
#include "../class_template/pq_unit_traits.hpp"
#include "../class_template/abstract_pq.hpp"
#include "../class_template/units_out.hpp"
#include "units_ostream.hpp"

namespace physical_quantities{

    template
    <
        typename Abstract_pq,
        typename Value_type,
        typename Units,
        quantity_mx Q_mx
    >
        inline physical_quantity_units_out
        < 
            Abstract_pq,
            Units,
            Q_mx
        >  
            units(p_quantity
                  <
                    Abstract_pq,
                    Value_type,
                    Units,
                    Q_mx
                  > const & )
            {
                return physical_quantity_units_out
                        < 
                            Abstract_pq,
                            Units,
                            Q_mx
                        >();
            }
 
// this is the default non member stream output function
// gives same output as member pq.units()
// but can be overridden as per examples below -->
   template
   <
        typename Abstract_pq,
        typename Units,
        quantity_mx Q_mx
   >
        inline std::ostream& 
            operator << 
                (std::ostream& os,
                    physical_quantity_units_out
                    < 
                        Abstract_pq,
                        Units,
                        Q_mx
                    > const&  )
            {
                os <<   p_quantity<
                            Abstract_pq,
                            pq_default_value_type,
                            Units,
                            Q_mx
                        >::units();                
                return os;
            }

    //newtons
      inline  std::ostream& 
             operator << 
                (std::ostream& os,
                    physical_quantity_units_out
                                <
                                    abstract_pq< 1,-2,1>,
                                    pq_unit_traits
                                    <
                                        of_length::m,
                                        of_time::s,
                                        of_mass::kg
                                    >,
                                    of_quantity::null
                                >
                                const&  )
            {
                os << "N";
                return os;
            }  
    //newtons
      inline  std::ostream& 
             operator << 
                (std::ostream& os,
                    physical_quantity_units_out
                                <
                                    abstract_pq< 1,-2,1>,
                                    pq_unit_traits
                                    <
                                        of_length::m,
                                        of_time::s,
                                        of_mass::kg
                                    >,
                                    of_quantity::kgf_to_N
                                >
                                const&  )
            {
                os << "kgf";
                return os;
            }  
 //watts
      inline  std::ostream& 
             operator << 
                (std::ostream& os,
                    physical_quantity_units_out
                    <
                        abstract_pq<2,-3,1>,
                        pq_unit_traits
                        <
                            of_length::m,
                            of_time::s,
                            of_mass::kg
                        >,
                        of_quantity::null
                    >
                                const&  )
            {
                os << "W";
                return os;
            }  
    //joules
      inline  std::ostream& 
             operator << 
                (std::ostream& os,
                    physical_quantity_units_out
                    < 
                        abstract_pq<2,-2,1>,
                        pq_unit_traits
                        <
                            of_length::m,
                            of_time::s,
                            of_mass::kg
                        >,
                        of_quantity::null
                    > const&  )
            {
                os << "J";
                return os;
            }           
}
#endif
