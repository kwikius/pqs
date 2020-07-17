#ifndef PQS_SI_UNITS_RECIPROCAL_MASS_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_RECIPROCAL_MASS_UNIT_HPP_INCLUDED

#include <pqs/types/base_quantity/mass.hpp>
#include <pqs/systems/si/unit.hpp>

namespace pqs{ namespace si { namespace reciprocal_mass_unit{

   struct per_kg : si::normative_unit<exp_mass<-1>, exponent10<0> >{};

   struct per_g : si::normative_unit<exp_mass<-1>, exponent10<3> >{};

   struct per_mg : si::normative_unit<exp_mass<-1>, exponent10<6> >{};

   struct per_ug : si::normative_unit<exp_mass<-1>, exponent10<9> >{};

}}} // pqs::si::mass_unit

#endif //PQS_SI_UNITS_RECIPROCAL_MASS_UNIT_HPP_INCLUDED
