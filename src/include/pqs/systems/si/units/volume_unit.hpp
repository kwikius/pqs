#ifndef PQS_SI_UNITS_VOLUME_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_VOLUME_UNIT_HPP_INCLUDED

#include <pqs/systems/si/unit.hpp>
#include <pqs/types/derived_quantity/volume.hpp>

namespace pqs{ namespace si { namespace volume_unit{

   struct m3  : si::normative_unit<abstract_volume_t, exponent10< 0> >{};
   struct cm3 : si::normative_unit<abstract_volume_t, exponent10<-6> >{};
   struct mm3 : si::normative_unit<abstract_volume_t, exponent10<-9> >{};

#if 0
// todo
   struct ft3 :
      conversion< 
         decltype( si::length_unit::ft() ^ std::ratio<3>() )
      >
   {};
#endif

}}} // pqs::si::volume_unit

#endif //PQS_SI_UNITS_VOLUME_UNIT_HPP_INCLUDED
