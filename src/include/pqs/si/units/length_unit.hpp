#ifndef PQS_SI_UNITS_LENGTH_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_LENGTH_UNIT_HPP_INCLUDED

#include <pqs/concepts/dimension.hpp>
#include <pqs/si/unit.hpp>
#include <pqs/base_quantity/length.hpp>

namespace pqs{ namespace si { namespace length_unit{

   struct mm : pqs::si::unit< 
      exp_length<1>,
      unit_exp<-3>
   >{};

   struct ft : pqs::si::unit_conversion< 
      exp_length<1>, 
      conversion_factor<
        std::ratio<381,125>,
        unit_exp<-1>
      >
   >{};

}}} // pqs::si::length_unit

#endif //PQS_SI_UNITS_LENGTH_UNIT_HPP_INCLUDED
