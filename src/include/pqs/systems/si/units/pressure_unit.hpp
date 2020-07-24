#ifndef PQS_SI_UNITS_PRESSURE_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_PRESSURE_UNIT_HPP_INCLUDED

#include <pqs/systems/si/unit.hpp>
#include <pqs/types/derived_quantity/pressure.hpp>
#include <pqs/bits/named.hpp>

namespace pqs{ namespace si { namespace pressure_unit{

   struct Pa : named<"Pa">, pqs::si::normative_unit<
      abstract_pressure_t
   >{};

}}} // pqs::si::speed_unit


#endif // PQS_SI_UNITS_PRESSURE_UNIT_HPP_INCLUDED
