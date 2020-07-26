#ifndef PQS_SI_UNITS_PRESSURE_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_PRESSURE_UNIT_HPP_INCLUDED

#include <pqs/systems/si/unit.hpp>
#include <pqs/types/derived_quantity/pressure.hpp>
#include <pqs/bits/named.hpp>

namespace pqs{ namespace si { namespace pressure_unit{

   struct Pa : named_si_unit<"Pa", abstract_pressure_t >{};
   struct kPa : named_si_unit<"kPa", abstract_pressure_t ,exponent10<3> >{};
   struct MPa : named_si_unit<"MPa", abstract_pressure_t ,exponent10<6> >{};

}}} // pqs::si::speed_unit


#endif // PQS_SI_UNITS_PRESSURE_UNIT_HPP_INCLUDED
