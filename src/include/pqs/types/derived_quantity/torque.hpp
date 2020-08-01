#ifndef PQS_DERIVED_QUANTITY_TORQUE_HPP_INCLUDED
#define PQS_DERIVED_QUANTITY_TORQUE_HPP_INCLUDED

#include <pqs/types/derived_quantity/force.hpp>
#include <pqs/types/base_quantity/length.hpp>

namespace pqs{
  
   struct abstract_torque_t : decltype( abstract_force_v * abstract_length_v ){};
   constexpr inline auto abstract_torque_v = abstract_torque_t{};
}

#endif // PQS_DERIVED_QUANTITY_TORQUE_UNIT_HPP_INCLUDED
