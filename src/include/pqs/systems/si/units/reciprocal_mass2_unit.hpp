#ifndef PQS_SI_UNITS_RECIPROCAL_MASS2_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_RECIPROCAL_MASS2_UNIT_HPP_INCLUDED

#include <pqs/types/base_quantity/mass.hpp>
#include <pqs/systems/si/unit.hpp>

namespace pqs{ namespace si { namespace reciprocal_mass2_unit{

   struct per_kg2 : si::normative_unit<exp_mass<-2>, exponent10<0> >{};

   struct per_g2 : si::normative_unit<exp_mass<-2>, exponent10<6> >{};

   struct per_mg2 : si::normative_unit<exp_mass<-2>, exponent10<12> >{};

   struct per_ug2 : si::normative_unit<exp_mass<-2>, exponent10<18> >{};

}}} // pqs::si::mass2_unit

#endif //PQS_SI_UNITS_RECIPROCAL_MASS2_UNIT_HPP_INCLUDED
