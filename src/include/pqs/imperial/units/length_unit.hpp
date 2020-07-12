#ifndef PQS_IMPERIAL_LENGTH_UNIT_HPP_INCLUDED
#define PQS_IMPERIAL_LENGTH_UNIT_HPP_INCLUDED

#include <pqs/imperial/unit.hpp>
#include <pqs/base_quantity/length.hpp>
#include <pqs/type_templates/conversion_factor.hpp>

namespace pqs{ namespace imperial { namespace length_unit{

   struct ft : 
      pqs::imperial::base_unit<
         decltype( abstract_length<> )
      >
   {};

   struct yd : named<"yd">,
      decltype( ft{} * std::ratio<3>{} )
   {};

   struct mi : named<"mi">,
      decltype( yd{} * std::ratio<1760>{} ) 
   {};

}}} // pqs::si::length_unit


#endif // PQS_IMPERIAL_LENGTH_UNIT_HPP_INCLUDED
