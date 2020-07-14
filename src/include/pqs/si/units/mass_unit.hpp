#ifndef PQS_SI_UNITS_MASS_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_MASS_UNIT_HPP_INCLUDED

#include <pqs/base_quantity/mass.hpp>
#include <pqs/si/unit.hpp>

namespace pqs{ namespace si { namespace mass_unit{

   struct kg : si::base_unit<base_mass>{};

   struct g : si::normative_unit<exp_mass<1>, exponent10<-3> >{};

}}} // pqs::si::mass_unit

#endif //PQS_SI_UNITS_MASS_UNIT_HPP_INCLUDED
