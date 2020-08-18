#ifndef PQS_SYSTEMS_SI_UNITS_CAPACITANCE_UNIT_HPP_INCLUDED
#define PQS_SYSTEMS_SI_UNITS_CAPACITANCE_UNIT_HPP_INCLUDED

#include <pqs/types/derived_quantity/capacitance.hpp>
#include <pqs/concepts/associated/get_derived_quantity_symbol.hpp>
#include <pqs/systems/si/unit.hpp>

namespace pqs{

  /**
   * @brief specialise symbol for capacitance in si measurement system
   */
   template <typename CharSet>
   inline constexpr 
   basic_fixed_string get_derived_quantity_symbol<
      abstract_capacitance_t, 
      si_measurement_system,
      CharSet
   > = "F";

}

namespace pqs::si::capacitance_unit{

   struct F : normative_unit<abstract_capacitance_t>{};
   struct mF : normative_unit<abstract_capacitance_t, exponent10<-3> >{};
   struct uF : normative_unit<abstract_capacitance_t, exponent10<-6> >{};
   struct nF : normative_unit<abstract_capacitance_t, exponent10<-9> >{};
   struct pF : normative_unit<abstract_capacitance_t, exponent10<-12> >{};

} // pqs::si::capacitance_unit

#endif // PQS_SYSTEMS_SI_UNITS_CAPACITANCE_UNIT_HPP_INCLUDED
