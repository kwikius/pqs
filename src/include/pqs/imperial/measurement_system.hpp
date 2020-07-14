#ifndef PQS_IMPERIAL_MEASUREMENT_SYSTEM_HPP_INCLUDED
#define PQS_IMPERIAL_MEASUREMENT_SYSTEM_HPP_INCLUDED

#include <pqs/bits/base_quantities.hpp>
#include <pqs/value_functions/get_base_unit_symbol.hpp>

namespace pqs { 

   struct imperial_measurement_system { 
      using type = imperial_measurement_system; 
   };

}

namespace pqs{
   namespace impl{
      template <> struct is_measurement_system_impl<
         pqs::imperial_measurement_system
      > : std::true_type{};
   }
}

namespace pqs{

   template <typename Charset>
   inline constexpr pqs::basic_fixed_string
   get_base_unit_symbol<
      base_length,imperial_measurement_system,Charset
   > = "ft";

   template <>
   inline constexpr pqs::basic_fixed_string
   get_base_unit_symbol<
      base_length,imperial_measurement_system,charset_utf8
   > = "\u0192\u01AB"; 

   template <typename Charset>
   inline constexpr pqs::basic_fixed_string
   get_base_unit_symbol<
      base_mass,imperial_measurement_system,Charset
   > = "lb";

   template <typename Charset>
   inline constexpr pqs::basic_fixed_string
   get_base_unit_symbol<
      base_time,imperial_measurement_system,Charset
   > = "s";

}

#endif // PQS_IMPERIAL_MEASUREMENT_SYSTEM_HPP_INCLUDED