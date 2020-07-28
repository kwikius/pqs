#ifndef PQS_SYSTEMS_SI_UNITS_ENERGY_UNIT_HPP_INCLUDED
#define PQS_SYSTEMS_SI_UNITS_ENERGY_UNIT_HPP_INCLUDED

#include <pqs/systems/si/units/force_unit.hpp>
#include <pqs/systems/si/units/length_unit.hpp>
#include <pqs/types/derived_quantity/energy.hpp>
#include <pqs/concepts/associated/unit_to_fixed_string.hpp>

namespace pqs{

  /**
   * @brief specialise symbol for energy in si measurement system
   */
   template <typename CharSet>
   inline constexpr 
   basic_fixed_string 
   get_derived_quantity_symbol<
      abstract_energy_t, 
      si_measurement_system,
      CharSet
   > = "J";

}

namespace pqs::si::energy_unit{

   struct J : normative_unit<abstract_energy_t>{};
   struct mJ: normative_unit<abstract_energy_t,exponent10<-3> >{};
   struct kJ: normative_unit<abstract_energy_t,exponent10<3> >{};
}

#endif // PQS_SYSTEMS_SI_UNITS_ENERGY_UNIT_HPP_INCLUDED
