#ifndef PQS_SI_UNITS_FORCE_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_FORCE_UNIT_HPP_INCLUDED

#include <pqs/types/derived_quantity/force.hpp>
#include <pqs/systems/si/unit.hpp>
#include <pqs/bits/named.hpp>

/**
  force unit namespace
*/
namespace pqs::si::force_unit{

  /**
   * @brief SI named unit demo
   */
   struct N : named_si_unit<"N", abstract_force_t>{};

  /**
   * @brief  prefixed named unit demo : mN
   */
   struct mN : named_si_unit<"mN", abstract_force_t, exponent10<-3> >{};

  /**
   * @brief  prefixed named unit demo : kN
   */
   struct kN : named_si_unit<"kN", abstract_force_t, exponent10<3> >{};

} // pqs::si::force_unit

#endif // PQS_SI_UNITS_FORCE_UNIT_HPP_INCLUDED
