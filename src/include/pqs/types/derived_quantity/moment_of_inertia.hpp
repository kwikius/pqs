#ifndef PQS_DERIVED_QUANTITY_MOMENT_OF_INERTIA_UNIT_HPP_INCLUDED
#define PQS_DERIVED_QUANTITY_MOMENT_OF_INERTIA_UNIT_HPP_INCLUDED

#include <pqs/types/base_quantity/mass.hpp>
#include <pqs/types/base_quantity/length.hpp>

namespace pqs{
  
   constexpr inline auto abstract_moment_of_inertia_v = abstract_mass_v * abstract_length_v * abstract_length_v;
   using abstract_moment_of_inertia_t = std::remove_cvref_t<decltype(abstract_moment_of_inertia_v)>;
}

#endif // PQS_DERIVED_QUANTITY_MOMENT_OF_INERTIA_UNIT_HPP_INCLUDED
