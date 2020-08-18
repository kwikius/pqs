#ifndef PQS_SYSTEMS_SI_UNITS_POWER_UNIT_HPP_INCLUDED
#define PQS_SYSTEMS_SI_UNITS_POWER_UNIT_HPP_INCLUDED

#include <pqs/types/derived_quantity/power.hpp>
#include <pqs/concepts/associated/get_derived_quantity_symbol.hpp>
#include <pqs/systems/si/unit.hpp>

namespace pqs{

  /**
   * @brief specialise symbol for power in si measurement system
   */
   template <typename CharSet>
   inline constexpr 
   basic_fixed_string 
   get_derived_quantity_symbol<
      abstract_power_t, 
      si_measurement_system,
      CharSet
   > = "W";

}

namespace pqs::si::power_unit{

   struct W  : normative_unit<abstract_power_t>{};
   struct mW : normative_unit<abstract_power_t,exponent10<-3> >{};
   struct kW : normative_unit<abstract_power_t,exponent10<3> >{};
}

#endif // PQS_SYSTEMS_SI_UNITS_POWER_UNIT_HPP_INCLUDED
