#ifndef PQS_TYPES_DERIVED_QUANTITY_VOLTAGE_HPP_INCLUDED
#define PQS_TYPES_DERIVED_QUANTITY_VOLTAGE_HPP_INCLUDED

#include <pqs/types/derived_quantity/energy.hpp>
#include <pqs/types/derived_quantity/charge.hpp>

namespace pqs{

   struct abstract_voltage_t : decltype(abstract_energy_v / abstract_charge_v){};
   constexpr inline auto abstract_voltage_v = abstract_voltage_t{};
}

#endif // PQS_TYPES_DERIVED_QUANTITY_VOLTAGE_HPP_INCLUDED
