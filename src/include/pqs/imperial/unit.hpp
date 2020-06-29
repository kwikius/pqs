#ifndef PQS_IMPERIAL_UNIT_HPP_INCLUDED
#define PQS_IMPERIAL_UNIT_HPP_INCLUDED

#include <pqs/bits/basic_unit.hpp>
#include <pqs/imperial/measurement_system.hpp>

namespace pqs{ namespace imperial{

   template <typename Dimension>
   struct base_unit : pqs::basic_unit<
      pqs::imperial::measurement_system,
      Dimension,
      conversion_factor<std::ratio<1>, std::ratio<0> > 
   >{
      using type = unit;
   };

   template <typename Dimension, typename ConversionFactor>
   struct unit_conversion : pqs::basic_unit<
      pqs::imperial::measurement_system, 
      Dimension, 
      ConversionFactor
   >{
      using type = unit_conversion;
   };

}}// pqs::imperial

#endif // PQS_SI_UNIT_HPP_INCLUDED
