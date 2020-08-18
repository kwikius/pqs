#ifndef PQS_SYSTEMS_SI_UNITS_CHARGE_UNIT_HPP_INCLUDED
#define PQS_SYSTEMS_SI_UNITS_CHARGE_UNIT_HPP_INCLUDED

#include <pqs/types/derived_quantity/charge.hpp>
#include <pqs/concepts/associated/get_derived_quantity_symbol.hpp>
#include <pqs/systems/si/unit.hpp>

namespace pqs{

  /**
   * @brief specialise symbol for charge in si measurement system
   */
   template <typename CharSet>
   inline constexpr 
   basic_fixed_string get_derived_quantity_symbol<
      abstract_charge_t, 
      si_measurement_system,
      CharSet
   > = "C";

}

namespace pqs::si::charge_unit{

   struct C : normative_unit<abstract_charge_t>{};
   struct mC : normative_unit<abstract_charge_t, exponent10<-3> >{};

} // pqs::si::force_unit

#endif // PQS_SYSTEMS_SI_UNITS_CHARGE_UNIT_HPP_INCLUDED
