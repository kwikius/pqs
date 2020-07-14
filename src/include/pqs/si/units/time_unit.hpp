#ifndef PQS_SI_UNITS_TIME_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_TIME_UNIT_HPP_INCLUDED

#include <pqs/base_quantity/time.hpp>
#include <pqs/si/unit.hpp>
#include <pqs/bits/fixed_string.hpp>

namespace pqs{ namespace si { namespace time_unit{

   template <typename ConversionFactor>
   struct conversion : 
   pqs::si::unit_conversion<
      decltype(abstract_time<>),
      ConversionFactor
   >{};

   struct s : si::base_unit<base_time>{};

   struct ms : si::proper_unit<exp_time<1>, exponent10<-3> >{};

   struct min : named<"min"> ,
      conversion< 
         decltype( std::ratio<1,60>{} ^ exponent10<0>{} )
      >
   {};

}}} // pqs::si::time_unit

#endif //PQS_SI_UNITS_TIME_UNIT_HPP_INCLUDED
