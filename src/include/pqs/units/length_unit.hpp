#ifndef PQS_UNITS_LENGTH_UNIT_HPP_INCLUDED
#define PQS_UNITS_LENGTH_UNIT_HPP_INCLUDED

#include <pqs/bits/base_dimension.hpp>
#include <pqs/bits/dimension.hpp>
#include <pqs/bits/unit.hpp>

// length unit definition namespace 
namespace pqs{ namespace length_unit{

   struct mm : unit< 
      dimension<dim_length<1> > 
      ,-3
   >{};

   struct ft : unit_conversion< 
      unit< 
         dimension<dim_length<1> >
         ,-1
      >
      ,381,125
    >{};

}} // pqs::length_unit

#endif // PQS_UNITS_LENGTH_UNIT_HPP_INCLUDED
