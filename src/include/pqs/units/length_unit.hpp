#ifndef PQS_UNITS_LENGTH_UNIT_HPP_INCLUDED
#define PQS_UNITS_LENGTH_UNIT_HPP_INCLUDED

#include <pqs/bits/dimension.hpp>
#include <pqs/bits/unit.hpp>
#include <pqs/base_quantity/length.hpp>

// length unit definition namespace 
namespace pqs{ namespace length_unit{

   struct mm : pqs::base_unit< 
      pqs::exp_length<1> ,
      -3
   >{};

   struct ft : pqs::unit_conversion< 
      pqs::base_unit< 
         pqs::exp_length<1>, 
         -1
      >
      ,381,125
    >{};

}} // pqs::length_unit

#endif //PQS_UNITS_LENGTH_UNIT_HPP_INCLUDED
