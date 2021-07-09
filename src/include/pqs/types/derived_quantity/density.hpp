#ifndef PQS_DERIVED_QUANTITY_DENSITY_UNIT_HPP_INCLUDED
#define PQS_DERIVED_QUANTITY_DENSITY_UNIT_HPP_INCLUDED

#include <pqs/types/base_quantity/mass.hpp>
#include <pqs/types/derived_quantity/volume.hpp>

namespace pqs{

   constexpr inline auto abstract_density_v = abstract_mass_v / abstract_volume_v;
   using abstract_density_t = std::remove_cvref_t<decltype(abstract_density_v)>;

}

#endif // PQS_DERIVED_QUANTITY_DENSITY_UNIT_HPP_INCLUDED
