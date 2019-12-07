#ifndef PQS_SI_LENGTH_UNIT_HPP_INCLUDED
#define PQS_SI_LENGTH_UNIT_HPP_INCLUDED

#include <pqs/si/base_dimension.hpp>
#include <pqs/dimension.hpp>
#include <pqs/si/unit.hpp>

// si length unit definition namespace 
namespace pqs{ namespace si{ namespace length_unit{

   struct mm : si::unit< 
      pqs::dimension<pqs::si::dim_length<1> > 
      ,-3
   >{};

   struct ft : si::unit_conversion< 
      si::unit< 
         pqs::dimension<pqs::si::dim_length<1> >
         ,-1
      >
      ,381,125
    >{};

}}} // pqs::si::length_unit

#endif // PQS_SI_LENGTH_UNIT_HPP_INCLUDED
