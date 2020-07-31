#ifndef PQS_SYSTEMS_SI_UNITS_CURRENT_UNIT_HPP_INCLUDED
#define PQS_SYSTEMS_SI_UNITS_CURRENT_UNIT_HPP_INCLUDED

#include <pqs/types/base_quantity/current.hpp>

#include <pqs/concepts/associated/get_derived_quantity_symbol.hpp>
#include <pqs/systems/si/unit.hpp>

namespace pqs{

  /**
   * @brief specialise symbol for current in si measurement system
   */
   template <typename CharSet>
   inline constexpr 
   basic_fixed_string get_derived_quantity_symbol<
      abstract_current_t, 
      si_measurement_system,
      CharSet
   > = "A";

}

namespace pqs::si::current_unit{

   struct A : normative_unit<abstract_current_t>{};
   struct mA : normative_unit<abstract_current_t, exponent10<-3> >{};
   struct uA : normative_unit<abstract_current_t, exponent10<-6> >{};
   struct nA : normative_unit<abstract_current_t, exponent10<-9> >{};
   struct pA : normative_unit<abstract_current_t, exponent10<-12> >{};
   struct fA : normative_unit<abstract_current_t, exponent10<-15> >{};

} // pqs::si::force_unit

#endif // PQS_SYSTEMS_SI_UNITS_CURRENT_UNIT_HPP_INCLUDED
