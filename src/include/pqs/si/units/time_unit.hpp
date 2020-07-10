#ifndef PQS_SI_UNITS_TIME_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_TIME_UNIT_HPP_INCLUDED

#include <pqs/base_quantity/time.hpp>
#include <pqs/si/unit.hpp>
#include <pqs/bits/fixed_string.hpp>

namespace pqs{ namespace si { namespace time_unit{

   template <
      pqs::basic_fixed_string Name, 
      typename Exp = exponent10<0> 
   >
   struct proper : pqs::si::proper_unit<
      decltype(abstract_time<1>),
      Exp
   >{
      static constexpr basic_fixed_string name = Name;
   };

   template <typename ConversionFactor>
   struct conversion : 
   pqs::si::unit_conversion<
      decltype(abstract_time<>),
      ConversionFactor
   >{};

   struct s : proper<"s">{};

   struct ms : proper<"ms", exponent10<-3> >{};

   struct min : named<"min"> ,
      conversion< 
         decltype( std::ratio<1,60>{} ^ exponent10<0>{} )
      >
   {};

}}} // pqs::si::time_unit

#endif //PQS_SI_UNITS_TIME_UNIT_HPP_INCLUDED
