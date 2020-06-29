#ifndef PQS_IMPERIAL_LENGTH_UNIT_HPP_INCLUDED
#define PQS_IMPERIAL_LENGTH_UNIT_HPP_INCLUDED

#include <pqs/imperial/unit.hpp>
#include <pqs/base_quantity/length.hpp>
#include <pqs/type_templates/conversion_factor.hpp>

namespace pqs{ namespace imperial { namespace length_unit{

   struct ft : pqs::imperial::base_unit<
      pqs::exp_length<1>
   >, named<"ft"> {};

   struct yd : decltype( ft{} * std::ratio<3>{}), named<"yd"> {};

   struct mi : decltype( yd{} * std::ratio<1760>{}), named<"mi">{};

}}} // pqs::si::length_unit


#endif // PQS_IMPERIAL_LENGTH_UNIT_HPP_INCLUDED
