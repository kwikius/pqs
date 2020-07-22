#ifndef PQS_TYPES_DERIVED_QUANTITY_PRESSURE_HPP_INCLUDED
#define PQS_TYPES_DERIVED_QUANTITY_PRESSURE_HPP_INCLUDED

#include <pqs/types/derived_quantity/force.hpp>
#include <pqs/types/derived_quantity/area.hpp>

namespace pqs{
  
   constexpr inline auto abstract_pressure_v = abstract_force_v / abstract_area_v;
   using abstract_pressure_t = std::remove_cvref_t<decltype(abstract_pressure_v)>;
}

#endif // PQS_TYPES_DERIVED_QUANTITY_PRESSURE_HPP_INCLUDED
