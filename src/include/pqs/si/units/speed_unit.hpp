#ifndef PQS_SI_UNITS_SPEED_UNIT_HPP_INCLUDED
#define PQS_SI_UNITS_SPEED_UNIT_HPP_INCLUDED

#include <pqs/bits/dimension.hpp>
#include <pqs/base_quantity/length.hpp>
#include <pqs/base_quantity/time.hpp>

namespace pqs{ namespace si { namespace speed_unit{

   struct m_per_s : pqs::si::unit<
#if defined  __cpp_inline_variables
     decltype( exp_length_v<1> / exp_time_v<1>),
#else
      decltype( exp_length<1>{} / exp_time<1>{}),
#endif
      unit_exp<0>
   >{};

}}} // pqs::si::speed_unit

#endif // PQS_SI_UNITS_SPEED_UNIT_HPP_INCLUDED
