#ifndef PQS_TYPES_DERIVED_QUANTITY_INDUCTANCE_HPP_INCLUDED
#define PQS_TYPES_DERIVED_QUANTITY_INDUCTANCE_HPP_INCLUDED

#include <pqs/types/derived_quantity/voltage.hpp>
#include <pqs/types/base_quantity/current.hpp>
#include <pqs/types/base_quantity/time.hpp>

namespace pqs{

   struct abstract_inductance_t : decltype((abstract_voltage_v * abstract_time_v)/ abstract_current_v){};
   constexpr inline auto abstract_inductance_v = abstract_inductance_t{};
}

#endif // PQS_TYPES_DERIVED_QUANTITY_INDUCTANCE_HPP_INCLUDED
