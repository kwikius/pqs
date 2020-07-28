#ifndef PQS_SYSTEMS_SI_UNITS_TORQUE_UNIT_HPP_INCLUDED
#define PQS_SYSTEMS_SI_UNITS_TORQUE_UNIT_HPP_INCLUDED

#include <pqs/systems/si/units/force_unit.hpp>
#include <pqs/systems/si/units/length_unit.hpp>
#include <pqs/types/derived_quantity/torque.hpp>
#include <pqs/concepts/associated/unit_to_fixed_string.hpp>

namespace pqs{

  /**
   * @brief specialise symbol for torque in si measurement system
   *        making use of unit_binary_op for output only
   */
   template <typename CharSet>
   inline constexpr 
   basic_fixed_string get_derived_quantity_symbol<
      abstract_torque_t, 
      si_measurement_system,
      CharSet
   > = unit_to_fixed_string<
         decltype( pqs::si::force_unit::N() * pqs::si::length_unit::m() ),
         CharSet
       > ();

}

namespace pqs::si::torque_unit{

   struct N_m : normative_unit<abstract_torque_t>{};
   struct mN_m : normative_unit<abstract_torque_t,exponent10<-3> >{};
}

#endif // PQS_SYSTEMS_SI_UNITS_TORQUE_UNIT_HPP_INCLUDED
