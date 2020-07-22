#ifndef PQS_SI_UNITS_ACCELERATION_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_ACCELERATION_UNIT_HPP_INCLUDED

#include <pqs/types/derived_quantity/acceleration.hpp>
#include <pqs/systems/si/unit.hpp>

namespace pqs{ namespace si { namespace acceleration_unit{

   struct m_per_s2 : pqs::si::normative_unit<
      abstract_acceleration_t
   >{};

}}} // pqs::si::acceleration_unit

#endif // PQS_SI_UNITS_ACCELERATION_UNIT_HPP_INCLUDED
