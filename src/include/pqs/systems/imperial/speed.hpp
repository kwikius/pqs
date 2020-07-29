#ifndef PQS_IMPERIAL_SPEED_HPP_INCLUDED
#define PQS_IMPERIAL_SPEED_HPP_INCLUDED

#include <pqs/concepts/associated/make_quantity.hpp>
#include <pqs/systems/imperial/units/speed_unit.hpp>

namespace pqs::imperial::speed{
   
   template <typename ValueType = double>
   using ft_per_s = pqs::make_quantity<pqs::imperial::speed_unit::ft_per_s,ValueType>;

   template <typename ValueType = double>
   using yd_per_s = pqs::make_quantity<pqs::imperial::speed_unit::yd_per_s,ValueType>;

   template <typename ValueType = double>
   using mi_per_hr = pqs::make_quantity<pqs::imperial::speed_unit::mi_per_hr,ValueType>;

}

#endif // PQS_IMPERIAL_SPEED_HPP_INCLUDED
