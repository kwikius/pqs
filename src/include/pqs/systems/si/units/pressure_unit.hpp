#ifndef PQS_SI_UNITS_PRESSURE_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_PRESSURE_UNIT_HPP_INCLUDED

#include <pqs/systems/si/unit.hpp>
#include <pqs/types/derived_quantity/pressure.hpp>

namespace pqs{

  /**
   * @brief specialise symbol for pressure in si measurement system
   */
   template <typename CharSet>
   inline constexpr 
   basic_fixed_string get_derived_quantity_symbol<
      abstract_pressure_t, 
      si_measurement_system,
      CharSet
   > = "Pa";
}

namespace pqs::si::pressure_unit{

   struct Pa : normative_unit<abstract_pressure_t >{};
   struct kPa : normative_unit<abstract_pressure_t ,exponent10<3> >{};
   struct MPa : normative_unit<abstract_pressure_t ,exponent10<6> >{};

} // pqs::si::speed_unit

#endif // PQS_SI_UNITS_PRESSURE_UNIT_HPP_INCLUDED
