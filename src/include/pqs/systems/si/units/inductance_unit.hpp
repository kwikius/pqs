#ifndef PQS_SYSTEMS_SI_UNITS_INDUCTANCE_UNIT_HPP_INCLUDED
#define PQS_SYSTEMS_SI_UNITS_INDUCTANCE_UNIT_HPP_INCLUDED

#include <pqs/types/derived_quantity/inductance.hpp>

#include <pqs/concepts/associated/get_derived_quantity_symbol.hpp>
#include <pqs/systems/si/unit.hpp>

namespace pqs{

  /**
   * @brief specialise symbol for inductance in si measurement system
   */
   template <typename CharSet>
   inline constexpr 
   basic_fixed_string get_derived_quantity_symbol<
      abstract_inductance_t, 
      si_measurement_system,
      CharSet
   > = "H";

}

namespace pqs::si::inductance_unit{

   struct H : normative_unit<abstract_inductance_t>{};
   struct mH : normative_unit<abstract_inductance_t, exponent10<-3> >{};
   struct uH : normative_unit<abstract_inductance_t, exponent10<-6> >{};
   struct nH : normative_unit<abstract_inductance_t, exponent10<-9> >{};

} // pqs::si::force_unit

#endif // PQS_SYSTEMS_SI_UNITS_INDUCTANCE_UNIT_HPP_INCLUDED
