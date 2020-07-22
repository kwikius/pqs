#ifndef PQS_SI_UNITS_FORCE_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_FORCE_UNIT_HPP_INCLUDED

#include <pqs/types/derived_quantity/force.hpp>
#include <pqs/systems/si/unit.hpp>
#include <pqs/bits/named.hpp>

namespace pqs{ namespace si { namespace force_unit{

   struct N : named<"N">, pqs::si::normative_unit<
     abstract_force_t
   >{};

}}} // pqs::si::speed_unit

#endif // PQS_SI_UNITS_FORCE_UNIT_HPP_INCLUDED
