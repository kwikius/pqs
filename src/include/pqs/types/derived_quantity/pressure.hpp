#ifndef PQS_TYPES_DERIVED_QUANTITY_PRESSURE_HPP_INCLUDED
#define PQS_TYPES_DERIVED_QUANTITY_PRESSURE_HPP_INCLUDED

#include <pqs/types/derived_quantity/force.hpp>
#include <pqs/types/derived_quantity/area.hpp>

namespace pqs{

   struct abstract_pressure_t : decltype(abstract_force_v / abstract_area_v){};
   constexpr inline auto abstract_pressure_v = abstract_pressure_t{};
  
}

#endif // PQS_TYPES_DERIVED_QUANTITY_PRESSURE_HPP_INCLUDED
