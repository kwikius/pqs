#ifndef PQS_TYPES_DERIVED_QUANTITY_CHARGE_HPP_INCLUDED
#define PQS_TYPES_DERIVED_QUANTITY_CHARGE_HPP_INCLUDED

#include <pqs/types/base_quantity/current.hpp>
#include <pqs/types/base_quantity/time.hpp>

namespace pqs{

   struct abstract_charge_t : decltype(abstract_current_v * abstract_time_v){};
   constexpr inline auto abstract_charge_v = abstract_charge_t{};
}

#endif // PQS_TYPES_DERIVED_QUANTITY_CHARGE_HPP_INCLUDED
