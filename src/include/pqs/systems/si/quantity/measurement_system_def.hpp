#ifndef PQS_BITS_SI_QUANTITY_SYSTEM_DEF_HPP_INCLUDED
#define PQS_BITS_SI_QUANTITY_SYSTEM_DEF_HPP_INCLUDED

#include <pqs/concepts/measurement_system.hpp>
#include <pqs/concepts/associated/get_base_unit_symbol.hpp>
#include <pqs/concepts/quantity.hpp>
#include <pqs/systems/si/quantity/get_base_unit_prefix_offset.hpp>
#include <pqs/types/base_quantities.hpp>
#include <pqs/types/fixed_string.hpp>
#include <pqs/types/conversion_factor.hpp>

namespace pqs{ 

   struct  si_measurement_system {
      using type = si_measurement_system;
   };

} //pqs

namespace pqs{

   namespace impl{
      template <> struct is_measurement_system_impl<
         pqs::si_measurement_system
      > : std::true_type{};
   }
}

namespace pqs{

   namespace si{

      template <>
      inline constexpr int get_base_unit_prefix_offset<base_mass> = 3;

      template <quantity Lhs, quantity Rhs>
      inline constexpr bool are_in_si_measurement_system
         = std::is_same_v<get_measurement_system<Lhs>,si_measurement_system> &&
         std::is_same_v<get_measurement_system<Rhs>,si_measurement_system>
      ;

      template <base_quantity Q, typename CharSet>
      inline constexpr 
      basic_fixed_string get_unprefixed_base_unit_symbol = 
         pqs::get_base_unit_symbol<Q,si_measurement_system,CharSet>;

      template <typename CharSet>
      inline constexpr 
      basic_fixed_string get_unprefixed_base_unit_symbol<
         pqs::base_mass ,CharSet
      > = "g";
   }

}

#endif // PQS_BITS_SI_QUANTITY_SYSTEM_DEF_HPP_INCLUDED
