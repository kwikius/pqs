#ifndef PQS_IMPERIAL_SPEED_UNIT_HPP_INCLUDED
#define PQS_IMPERIAL_SPEED_UNIT_HPP_INCLUDED

#include <pqs/systems/imperial/units/length_unit.hpp>
#include <pqs/systems/imperial/units/time_unit.hpp>
#include <pqs/concepts/associated/unit_binary_op.hpp>

namespace pqs{ namespace imperial { namespace speed_unit{

   struct ft_per_s : 
      decltype( length_unit::ft() / time_unit::s() )
   {};

   struct yd_per_s :
      decltype( length_unit::yd() / time_unit::s() )
   {};

   struct mi_per_hr : 
      decltype( length_unit::mi() / time_unit::hr() ) 
   {};

}}} // pqs::si::length_unit


#endif // PQS_IMPERIAL_SPEED_UNIT_HPP_INCLUDED
