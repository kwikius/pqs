#ifndef PQS_SI_UNITS_SPEED_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_SPEED_UNIT_HPP_INCLUDED

#include <pqs/base_quantity/length.hpp>
#include <pqs/base_quantity/time.hpp>
#include <pqs/si/unit.hpp>

namespace pqs{ namespace si { namespace speed_unit{

   struct m_per_s : pqs::si::unit<
      decltype( abstract_length<> / abstract_time<>)
   >{};

}}} // pqs::si::speed_unit

#endif // PQS_SI_UNITS_SPEED_UNIT_HPP_INCLUDED
