#ifndef PQS_SI_UNITS_MASS_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_MASS_UNIT_HPP_INCLUDED

#include <pqs/types/base_quantity/mass.hpp>
#include <pqs/systems/si/unit.hpp>

namespace pqs{ namespace si { namespace mass_unit{

   struct kg : si::base_unit<base_mass>{};

   struct g : si::normative_unit<abstract_mass_t, exponent10<-3> >{};

   struct mg : si::normative_unit<abstract_mass_t, exponent10<-6> >{};

   struct ug : si::normative_unit<abstract_mass_t, exponent10<-9> >{};

}}} // pqs::si::mass_unit

#endif //PQS_SI_UNITS_MASS_UNIT_HPP_INCLUDED
