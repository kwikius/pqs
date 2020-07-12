#ifndef PQS_IMPERIAL_TIME_UNIT_HPP_INCLUDED
#define PQS_IMPERIAL_TIME_UNIT_HPP_INCLUDED

#include <pqs/imperial/unit.hpp>
#include <pqs/base_quantity/time.hpp>
#include <pqs/type_templates/conversion_factor.hpp>

namespace pqs{ namespace imperial { namespace time_unit{

   struct s :
      pqs::imperial::base_unit<
         decltype( abstract_time<> )
      >
   {};

   struct min : named<"min">,
      decltype( s{} * std::ratio<60>{} )
   {};

   struct hr : named<"hr">,
      decltype( min{} * std::ratio<60>{} ) 
   {};

}}} // pqs::si::time_unit


#endif // PQS_IMPERIAL_TIME_UNIT_HPP_INCLUDED
