#ifndef PQS_DERIVED_QUANTITY_DENSITY_UNIT_HPP_INCLUDED
#define PQS_DERIVED_QUANTITY_DENSITY_UNIT_HPP_INCLUDED

#include <pqs/types/base_quantity/mass.hpp>
#include <pqs/types/derived_quantity/volume.hpp>

namespace pqs{
  
   struct abstract_density_t : decltype ( abstract_mass_v / abstract_volume_v){};
   constexpr inline auto abstract_density_v = abstract_density_t{};
}

#endif // PQS_DERIVED_QUANTITY_DENSITY_UNIT_HPP_INCLUDED
