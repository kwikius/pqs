#ifndef PQS_DERIVED_QUANTITY_FORCE_UNIT_HPP_INCLUDED
#define PQS_DERIVED_QUANTITY_FORCE_UNIT_HPP_INCLUDED

#include <pqs/types/base_quantity/mass.hpp>
#include <pqs/types/derived_quantity/acceleration.hpp>

namespace pqs{
  
   constexpr inline auto abstract_force_v = abstract_mass_v * abstract_acceleration_v;
   using abstract_force_t = std::remove_cvref_t<decltype(abstract_force_v)>;
}

#endif // PQS_DERIVED_QUANTITY_FORCE_UNIT_HPP_INCLUDED
