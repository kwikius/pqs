#ifndef PQS_SYSTEMS_SI_UNITS_VOLTAGE_UNIT_HPP_INCLUDED
#define PQS_SYSTEMS_SI_UNITS_VOLTAGE_UNIT_HPP_INCLUDED

#include <pqs/types/derived_quantity/voltage.hpp>

#include <pqs/concepts/associated/get_derived_quantity_symbol.hpp>
#include <pqs/systems/si/unit.hpp>

namespace pqs{

  /**
   * @brief specialise symbol for voltage in si measurement system
   */
   template <typename CharSet>
   inline constexpr 
   basic_fixed_string get_derived_quantity_symbol<
      abstract_voltage_t, 
      si_measurement_system,
      CharSet
   > = "V";

}

namespace pqs::si::voltage_unit{

   struct V : normative_unit<abstract_voltage_t>{};
   struct mV : normative_unit<abstract_voltage_t, exponent10<-3> >{};
   struct uV : normative_unit<abstract_voltage_t, exponent10<-6> >{};
   struct nV : normative_unit<abstract_voltage_t, exponent10<-9> >{};
   struct pV : normative_unit<abstract_voltage_t, exponent10<-12> >{};
   struct fV : normative_unit<abstract_voltage_t, exponent10<-15> >{};

} // pqs::si::force_unit

#endif // PQS_SYSTEMS_SI_UNITS_VOLTAGE_UNIT_HPP_INCLUDED
