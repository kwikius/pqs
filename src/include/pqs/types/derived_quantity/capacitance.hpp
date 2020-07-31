#ifndef PQS_TYPES_DERIVED_QUANTITY_CAPACITANCE_HPP_INCLUDED
#define PQS_TYPES_DERIVED_QUANTITY_CAPACITANCE_HPP_INCLUDED

#include <pqs/types/derived_quantity/charge.hpp>
#include <pqs/types/derived_quantity/voltage.hpp>

namespace pqs{

   struct abstract_capacitance_t : decltype(abstract_charge_v / abstract_voltage_v){};
   constexpr inline auto abstract_capacitance_v = abstract_capacitance_t{};
}

#endif // PQS_TYPES_DERIVED_QUANTITY_CAPACITANCE_HPP_INCLUDED
