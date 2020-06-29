#ifndef PQS_SI_UNIT_HPP_INCLUDED
#define PQS_SI_UNIT_HPP_INCLUDED

#include <pqs/bits/basic_unit.hpp>
#include <pqs/si/measurement_system.hpp>

namespace pqs{ namespace si{

   template <typename Dimension, typename Exp = exponent10<0> >
   struct unit : pqs::basic_unit<
      pqs::si_measurement_system,
      Dimension,
      pqs::conversion_factor<std::ratio<1>, Exp > 
   >{
      using type = unit;
   };

   template <typename Dimension, typename ConversionFactor>
   struct unit_conversion : pqs::basic_unit<
      pqs::si_measurement_system, 
      Dimension, 
      ConversionFactor
   >{
      using type = unit_conversion;
   };

}}// pqs::si


#endif // PQS_SI_UNIT_HPP_INCLUDED
