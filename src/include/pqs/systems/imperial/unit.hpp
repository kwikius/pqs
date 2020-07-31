#ifndef PQS_IMPERIAL_UNIT_HPP_INCLUDED
#define PQS_IMPERIAL_UNIT_HPP_INCLUDED

#include <pqs/concepts/quantity.hpp>
#include <pqs/concepts/associated/make_unit.hpp>
#include <pqs/types/base_unit.hpp>
#include <pqs/systems/imperial/measurement_system.hpp>

namespace pqs{ namespace imperial{

   template <typename Dimension, typename ConversionFactor>
   struct unit_conversion : pqs::make_unit<
      pqs::imperial_measurement_system, 
      Dimension, 
      ConversionFactor
   >{
      using type = unit_conversion;
   };

}}// pqs::imperial

#endif // PQS_SI_UNIT_HPP_INCLUDED
