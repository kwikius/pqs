#ifndef PQS_SI_UNITS_FORCE_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_FORCE_UNIT_HPP_INCLUDED

#include <pqs/types/derived_quantity/force.hpp>
#include <pqs/concepts/associated/get_derived_quantity_symbol.hpp>
#include <pqs/systems/si/unit.hpp>
#include <pqs/bits/named.hpp>

namespace pqs{

  /**
   * @brief specialise symbol for force in si measurement system
   */
   template <typename CharSet>
   inline constexpr 
   basic_fixed_string get_derived_quantity_symbol<
      abstract_force_t, 
      si_measurement_system,
      CharSet
   > = "N";

}

/**
  force unit namespace
*/
namespace pqs::si::force_unit{

   struct N : normative_unit<abstract_force_t>{};
   struct mN : normative_unit<abstract_force_t, exponent10<-3> >{};
   struct kN : normative_unit<abstract_force_t, exponent10< 3> >{};
   struct uN : normative_unit<abstract_force_t, exponent10<-6> > {};

} // pqs::si::force_unit

#endif // PQS_SI_UNITS_FORCE_UNIT_HPP_INCLUDED
