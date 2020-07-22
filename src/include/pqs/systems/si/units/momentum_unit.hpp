#ifndef PQS_SI_UNITS_MOMENTUM_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_MOMENTUM_UNIT_HPP_INCLUDED

#include <pqs/systems/si/unit.hpp>
#include <pqs/types/derived_quantity/momentum.hpp>

namespace pqs{ namespace si { namespace momentum_unit{

   struct kg_m_per_s : pqs::si::normative_unit<
      abstract_momentum_t
   >{};

}}} // pqs::si::speed_unit

#endif // PQS_SI_UNITS_MOMENTUM_UNIT_HPP_INCLUDED
