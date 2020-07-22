#ifndef PQS_SI_UNITS_DENSITY_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_DENSITY_UNIT_HPP_INCLUDED

#include <pqs/systems/si/unit.hpp>
#include <pqs/types/derived_quantity/density.hpp>

namespace pqs{ namespace si { namespace density_unit{

   struct kg_per_m3  : si::normative_unit<abstract_density_t, exponent10< 0> >{};


}}} // pqs::si::density_unit

#endif //PQS_SI_UNITS_DENSITY_UNIT_HPP_INCLUDED
