#ifndef PQS_IMPERIAL_SPEED_HPP_INCLUDED
#define PQS_IMPERIAL_SPEED_HPP_INCLUDED

#include <pqs/imperial/units/speed_unit.hpp>

namespace pqs{ namespace imperial { namespace speed{
   
   template <typename ValueType = double>
   using ft_per_s = pqs::basic_quantity<pqs::imperial::speed_unit::ft_per_s,ValueType>;

   template <typename ValueType = double>
   using yd_per_s = pqs::basic_quantity<pqs::imperial::speed_unit::yd_per_s,ValueType>;

   template <typename ValueType = double>
   using mi_per_hr = pqs::basic_quantity<pqs::imperial::speed_unit::mi_per_hr,ValueType>;

}}}

#endif // PQS_IMPERIAL_SPEED_HPP_INCLUDED
