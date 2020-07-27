#ifndef PQS_SYSTEMS_SI_BASE_UNIT_SYMBOLS_HPP_INCLUDED
#define PQS_SYSTEMS_SI_BASE_UNIT_SYMBOLS_HPP_INCLUDED

#include <pqs/systems/si/quantity/measurement_system_def.hpp>
#include <pqs/types/base_quantities.hpp>
#include <pqs/types/fixed_string.hpp>
#include <pqs/concepts/associated/get_base_unit_symbol.hpp>

namespace pqs{

 template <typename Charset>
   inline constexpr pqs::basic_fixed_string
   get_base_unit_symbol<
      base_length,si_measurement_system,Charset
   > = "m";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string
   get_base_unit_symbol<
      base_mass,si_measurement_system,CharSet
   > = "kg";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string
   get_base_unit_symbol<
      base_time,si_measurement_system,CharSet
   > = "s";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string
   get_base_unit_symbol<
      base_current,si_measurement_system,CharSet
   > = "A";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string
   get_base_unit_symbol<
      base_temperature,si_measurement_system,CharSet
   > = "K";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string
   get_base_unit_symbol<
      base_substance,si_measurement_system,CharSet
   > = "mol";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string
   get_base_unit_symbol<
      base_intensity,si_measurement_system,CharSet
   > = "cd";

}

#endif // PQS_SYSTEMS_SI_BASE_UNIT_SYMBOLS_HPP_INCLUDED
