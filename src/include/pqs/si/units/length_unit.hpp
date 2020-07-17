#ifndef PQS_SI_UNITS_LENGTH_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_LENGTH_UNIT_HPP_INCLUDED

#include <pqs/base_quantity/length.hpp>
#include <pqs/si/unit.hpp>
#include <pqs/bits/named.hpp>

namespace pqs{ namespace si { namespace length_unit{

   struct m : si::base_unit<base_length>{};

   struct mm : si::normative_unit<exp_length<1>, exponent10<-3> >{};

   struct cm : si::normative_unit<exp_length<1>, exponent10<-2> >{};

   struct km : si::normative_unit<exp_length<1>, exponent10<3> >{};

// ------- unit conversions from other systems  -------- 

   template <typename ConversionFactor>
   struct conversion : 
   pqs::si::unit_conversion<
      decltype(abstract_length<>),
      ConversionFactor
   >{};

   struct ft : named<"ft"> ,
      conversion< 
         decltype( std::ratio<381,125>() ^ exponent10<-1>() )
      >
   {};

}}} // pqs::si::length_unit

#endif //PQS_SI_UNITS_LENGTH_UNIT_HPP_INCLUDED
