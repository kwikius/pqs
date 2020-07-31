#ifndef MAKE_UNIT_HPP_INCLUDED
#define MAKE_UNIT_HPP_INCLUDED

#include <pqs/concepts/associated/unit_definition.hpp>
#include <pqs/concepts/associated/measurement_system_definition.hpp>
#include <pqs/concepts/associated/dimension_definition.hpp>
#include <pqs/concepts/associated/get_conversion_factor.hpp>
#include <pqs/types/basic_unit.hpp>

namespace pqs{

   namespace impl{

      template <
         measurement_system Sm,
         dimension D, 
         typename ConversionFactor
      >
      struct make_unit_impl{
         using type = basic_unit<
            Sm,
            D,
            ConversionFactor
         >;
      };

   }// impl

   template <
      measurement_system Sm,
      dimension D, 
      typename ConversionFactor
   >
   using make_unit = 
      typename impl::make_unit_impl<
         Sm,D,ConversionFactor
      >::type;
}

#endif // MAKE_UNIT_HPP_INCLUDED
