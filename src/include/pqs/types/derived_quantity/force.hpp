#ifndef PQS_DERIVED_QUANTITY_FORCE_UNIT_HPP_INCLUDED
#define PQS_DERIVED_QUANTITY_FORCE_UNIT_HPP_INCLUDED

#include <pqs/types/base_quantity/mass.hpp>
#include <pqs/types/derived_quantity/acceleration.hpp>

namespace pqs{
  
   struct abstract_force_t : decltype(abstract_mass_v * abstract_acceleration_v){};
   constexpr inline auto abstract_force_v = abstract_force_t{};
}

#endif // PQS_DERIVED_QUANTITY_FORCE_UNIT_HPP_INCLUDED
