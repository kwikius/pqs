#ifndef PQS_UNITS_LENGTH_UNIT_HPP_INCLUDED
#define PQS_UNITS_LENGTH_UNIT_HPP_INCLUDED

#include <pqs/bits/dimension.hpp>
#include <pqs/bits/unit.hpp>
#include <pqs/base_quantity/length.hpp>

// length unit definition namespace 
namespace pqs{ namespace length_unit{

   struct mm : pqs::si_unit< 
      exp_length<1>,
      unit_exp<-3>
   >{};

   struct ft : pqs::si_unit_conversion< 
      exp_length<1>, 
      conversion_factor<
        std::ratio<381,125>,
        unit_exp<-1>
      >
   >{};

}} // pqs::length_unit

#endif //PQS_UNITS_LENGTH_UNIT_HPP_INCLUDED
