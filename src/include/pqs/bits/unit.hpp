#ifndef PQS_UNIT_HPP_INCLUDED
#define PQS_UNIT_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/bits/dimension.hpp>
#include <pqs/bits/conversion_factor.hpp>
#include <pqs/bits/si_quantity_system.hpp>
#include <pqs/bits/unit_exp.hpp>

/*
   unit : encapsulates quantity sytem, dimension and conversion factor
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

// move to si namespace ?
   template <typename Dimension, typename UnitExp>
   struct si_unit : basic_unit<
      si_quantity_system,
      Dimension, 
      conversion_factor<std::ratio<1>,UnitExp> 
   >{};

   template <typename Dimension, typename ConversionFactor>
   struct si_unit_conversion : basic_unit<
      si_quantity_system, 
      Dimension, 
      ConversionFactor
   >{};

}// pqs

#endif // PQS_UNIT_HPP_INCLUDED
