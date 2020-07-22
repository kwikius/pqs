#ifndef PQS_SI_UNITS_RECIPROCAL_AREA_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_RECIPROCAL_AREA_UNIT_HPP_INCLUDED

#include <pqs/systems/si/unit.hpp>
#include <pqs/types/base_quantity/length.hpp>

namespace pqs{ namespace si { namespace reciprocal_area_unit{

   struct per_m2 : si::normative_unit<exp_length<-2>,exponent10<0> >{};
   struct per_cm2 : si::normative_unit<exp_length<-2>, exponent10<4> >{};
   struct per_mm2 : si::normative_unit<exp_length<-2>, exponent10<6> >{};
   struct per_km2 : si::normative_unit<exp_length<-2>, exponent10<-6> >{};

#if 0
// todo
   struct ft2 :
      conversion< 
         decltype( si::length_unit::ft() ^ std::ratio<2>() )
      >
   {};
#endif

}}} // pqs::si::reciprocal_area_unit

#endif //PQS_SI_UNITS_RECIPROCAL_AREA_UNIT_HPP_INCLUDED
