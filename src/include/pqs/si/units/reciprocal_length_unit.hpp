#ifndef PQS_SI_UNITS_RECIPROCAL_LENGTH_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_RECIPROCAL_LENGTH_UNIT_HPP_INCLUDED

#include <pqs/base_quantity/length.hpp>
#include <pqs/si/unit.hpp>

namespace pqs{ namespace si { namespace reciprocal_length_unit{

   struct per_m : si::normative_unit<exp_length<-1>, exponent10<0> >{};

   struct per_mm : si::normative_unit<exp_length<-1>, exponent10<3> >{};

   struct per_cm : si::normative_unit<exp_length<-1>, exponent10<2> >{};

   struct per_km : si::normative_unit<exp_length<-1>, exponent10<-3> >{};

}}} // pqs::si::length_unit

#endif //PQS_SI_UNITS_RECIPROCAL_LENGTH_UNIT_HPP_INCLUDED
