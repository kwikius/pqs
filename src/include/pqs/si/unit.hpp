#ifndef UNIT_HPP_INCLUDED
#define UNIT_HPP_INCLUDED

#include <pqs/bits/basic_unit.hpp>
#include <pqs/bits/si_quantity_system.hpp>

namespace pqs{ namespace si{

   template <typename Dimension, typename UnitExp>
   struct unit : basic_unit<
      si_quantity_system,
      Dimension, 
      conversion_factor<std::ratio<1>,UnitExp> 
   >{};

   template <typename Dimension, typename ConversionFactor>
   struct unit_conversion : basic_unit<
      si_quantity_system, 
      Dimension, 
      ConversionFactor
   >{};

}}// pqs::si


#endif // UNIT_HPP_INCLUDED
