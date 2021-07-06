#ifndef PQS_SI_UNITS_TEMPERATURE_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_TEMPERATURE_UNIT_HPP_INCLUDED

#include <pqs/systems/si/unit.hpp>
#include <pqs/types/base_quantity/temperature.hpp>
#include <pqs/bits/named.hpp>

namespace pqs{ namespace si { namespace temperature_unit{

   struct K : si::base_unit<base_temperature>{};

}}} // pqs::si::temperature_unit

#endif //PQS_SI_UNITS_TEMPERATURE_UNIT_HPP_INCLUDED
