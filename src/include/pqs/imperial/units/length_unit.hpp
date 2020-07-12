#ifndef PQS_IMPERIAL_LENGTH_UNIT_HPP_INCLUDED
#define PQS_IMPERIAL_LENGTH_UNIT_HPP_INCLUDED

#include <pqs/imperial/unit.hpp>
#include <pqs/base_quantity/length.hpp>

namespace pqs{ namespace imperial { namespace length_unit{

   struct ft : pqs::base_unit<
      base_length,imperial_measurement_system
   >{};

   struct yd : named<"yd">,
      decltype( ft{} * std::ratio<3>{} )
   {};

   struct mi : named<"mi">,
      decltype( yd{} * std::ratio<1760>{} ) 
   {};

}}} // pqs::si::length_unit


#endif // PQS_IMPERIAL_LENGTH_UNIT_HPP_INCLUDED
