#ifndef PQS_SI_UNITS_AREA_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_AREA_UNIT_HPP_INCLUDED

#include <pqs/types/base_quantity/length.hpp>
#include <pqs/systems/si/unit.hpp>

namespace pqs{ namespace si { namespace area_unit{

   struct m2 : si::normative_unit<exp_length<2>,exponent10<0> >{};
   struct cm2 : si::normative_unit<exp_length<2>, exponent10<-4> >{};
   struct mm2 : si::normative_unit<exp_length<2>, exponent10<-6> >{};

#if 0
// todo
   struct ft2 :
      conversion< 
         decltype( si::length_unit::ft() ^ std::ratio<2>() )
      >
   {};
#endif

}}} // pqs::si::area_unit

#endif //PQS_SI_UNITS_AREA_UNIT_HPP_INCLUDED
