#ifndef PQS_SI_UNITS_SPEED_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_SPEED_UNIT_HPP_INCLUDED

#include <pqs/systems/si/unit.hpp>
#include <pqs/types/derived_quantity/speed.hpp>

namespace pqs{ namespace si { namespace speed_unit{

   struct m_per_s : pqs::si::normative_unit<
      abstract_speed_t
   >{};

}}} // pqs::si::speed_unit

#endif // PQS_SI_UNITS_SPEED_UNIT_HPP_INCLUDED
