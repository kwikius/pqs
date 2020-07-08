#ifndef PQS_SI_UNITS_LENGTH_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_LENGTH_UNIT_HPP_INCLUDED

#include <pqs/base_quantity/length.hpp>
#include <pqs/si/unit.hpp>
#include <pqs/bits/fixed_string.hpp>

namespace pqs{ namespace si { namespace length_unit{

   //for si units is_base_of<si::unit,T> is true
   template <
      pqs::basic_fixed_string Name, 
      typename Exp = exponent10<0> 
   >
   struct proper : pqs::si::proper_unit<
      decltype(abstract_length<1>),
      Exp
   >{
      static constexpr basic_fixed_string name = Name;
   };

    //for si unit_conversions is_base_of<si::unit_conversion,T> is true
   template <typename ConversionFactor>
   struct conversion : 
   pqs::si::unit_conversion<
      decltype(abstract_length<>),
      ConversionFactor
   >{};

   struct m : proper<"m">{};

   struct mm : proper<"mm", exponent10<-3> >{};

   struct ft : named<"ft"> ,
      conversion< 
         decltype( std::ratio<381,125>{}^exponent10<-1>{} )
      >
   {};

}}} // pqs::si::length_unit

#endif //PQS_SI_UNITS_LENGTH_UNIT_HPP_INCLUDED
