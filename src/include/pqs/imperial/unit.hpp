#ifndef PQS_IMPERIAL_UNIT_HPP_INCLUDED
#define PQS_IMPERIAL_UNIT_HPP_INCLUDED

#include <pqs/bits/basic_unit.hpp>
#include <pqs/type_templates/base_unit.hpp>
#include <pqs/imperial/measurement_system.hpp>

namespace pqs{ namespace imperial{

   template <typename Dimension, typename ConversionFactor>
   struct unit_conversion : pqs::basic_unit<
      pqs::imperial_measurement_system, 
      Dimension, 
      ConversionFactor
   >{
      using type = unit_conversion;
   };

}}// pqs::imperial

#endif // PQS_SI_UNIT_HPP_INCLUDED
