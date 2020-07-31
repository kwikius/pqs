#ifndef PQS_BITS_BASIC_UNIT_FWD_HPP_INCLUDED
#define PQS_BITS_BASIC_UNIT_FWD_HPP_INCLUDED

#include <pqs/concepts/associated/unit_definition.hpp>
#include <pqs/concepts/associated/measurement_system_definition.hpp>
#include <pqs/concepts/associated/dimension_definition.hpp>
#include <pqs/concepts/associated/get_conversion_factor.hpp>

namespace pqs{

   template <
      typename MeasurementSystem,
      typename Dimension, 
      typename ConversionFactor
   >
   struct basic_unit;


} // pqs

#endif // PQS_BITS_BASIC_UNIT_FWD_HPP_INCLUDED
