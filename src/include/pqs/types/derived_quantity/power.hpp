#ifndef PQS_DERIVED_QUANTITY_POWER_HPP_INCLUDED
#define PQS_DERIVED_QUANTITY_POWER_HPP_INCLUDED

#include <pqs/types/derived_quantity/energy.hpp>
#include <pqs/types/base_quantity/time.hpp>

namespace pqs{
  
   struct abstract_power_t : decltype( abstract_energy_v / abstract_time_v ){};
   constexpr inline auto abstract_power_v = abstract_power_t{};
}

#endif // PQS_DERIVED_QUANTITY_POWER_HPP_INCLUDED
