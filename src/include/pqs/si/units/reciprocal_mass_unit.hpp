#ifndef PQS_SI_UNITS_RECIPROCAL_MASS_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_RECIPROCAL_MASS_UNIT_HPP_INCLUDED

#include <pqs/base_quantity/mass.hpp>
#include <pqs/si/unit.hpp>

namespace pqs{ namespace si { namespace reciprocal_mass_unit{

   struct per_kg : si::proper_unit<exp_mass<-1>, exponent10<0> >{};

   struct per_g : si::proper_unit<exp_mass<-1>, exponent10<3> >{};

   struct per_mg : si::proper_unit<exp_mass<-1>, exponent10<6> >{};

   struct per_ug : si::proper_unit<exp_mass<-1>, exponent10<9> >{};

}}} // pqs::si::mass_unit

#endif //PQS_SI_UNITS_RECIPROCAL_MASS_UNIT_HPP_INCLUDED
