#ifndef PQS_SI_UNITS_LENGTH_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_LENGTH_UNIT_HPP_INCLUDED

#include <pqs/concepts/dimension.hpp>
#include <pqs/si/unit.hpp>
#include <pqs/base_quantity/length.hpp>
#include <pqs/bits/named.hpp>

namespace pqs{ namespace si { namespace length_unit{

   template <typename exp = exponent10<0> >
   using coherent_length_unit = 
   pqs::si::unit<
      decltype(abstract_length<1>),
      exp
   >;

   template <typename ConversionFactor>
   using length_unit_conversion = 
   pqs::si::unit_conversion<
      decltype(abstract_length<>),
      ConversionFactor
   >;

   struct m : coherent_length_unit<>{};

   struct mm : coherent_length_unit< exponent10<-3> >{};

   struct ft : named<"ft"> ,
      length_unit_conversion< 
         decltype( std::ratio<381,125>{} * exponent10<-1>{} )
      >
   {};

}}} // pqs::si::length_unit

#endif //PQS_SI_UNITS_LENGTH_UNIT_HPP_INCLUDED
