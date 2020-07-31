#ifndef PQS_TYPES_DERIVED_QUANTITY_RESISTANCE_HPP_INCLUDED
#define PQS_TYPES_DERIVED_QUANTITY_RESISTANCE_HPP_INCLUDED

#include <pqs/types/derived_quantity/voltage.hpp>
#include <pqs/types/base_quantity/current.hpp>

namespace pqs{

   struct abstract_resistance_t : decltype(abstract_voltage_v / abstract_current_v){};
   constexpr inline auto abstract_resistance_v = abstract_resistance_t{};
}

#endif // PQS_TYPES_DERIVED_QUANTITY_RESISTANCE_HPP_INCLUDED
