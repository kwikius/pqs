#ifndef PQS_BASIC_UNIT_HPP_INCLUDED
#define PQS_BASIC_UNIT_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/concepts/dimension.hpp>
#include <pqs/type_templates/conversion_factor.hpp>
//#include <pqs/type_templates/unit_exp.hpp>

/*
   basic_unit : encapsulates quantity system, dimension and conversion factor
   but without the numeric value.
*/

namespace pqs{ 

   template <
      typename QuantitySystem,
      typename Dim, 
      typename ConversionFactor
   >
   struct basic_unit{
      typedef QuantitySystem quantity_system;
      typedef Dim dimension;
      typedef ConversionFactor conversion_factor;
   };

}// pqs

#endif // PQS_BASIC_UNIT_HPP_INCLUDED
