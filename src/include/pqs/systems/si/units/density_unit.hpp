#ifndef PQS_SI_UNITS_DENSITY_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_DENSITY_UNIT_HPP_INCLUDED

#include <pqs/systems/si/unit.hpp>
#include <pqs/types/derived_quantity/density.hpp>

namespace pqs{

   /**
   * @brief specialise symbol for density in si measurement system
   **/
   template <typename CharSet>
   inline constexpr 
   basic_fixed_string get_derived_quantity_symbol<
      abstract_density_t, 
      si_measurement_system,
      CharSet
   > = pqs::basic_fixed_string{"kg/m"} + detail::superscript_integer<3,CharSet>;
}

namespace pqs{ namespace si { namespace density_unit{

   struct kg_per_m3  : si::normative_unit<abstract_density_t, exponent10< 0> >{};

}}} // pqs::si::density_unit

#endif //PQS_SI_UNITS_DENSITY_UNIT_HPP_INCLUDED
