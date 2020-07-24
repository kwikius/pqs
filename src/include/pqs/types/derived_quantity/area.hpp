#ifndef PQS_TYPES_DERIVED_QUANTITY_AREA_HPP_INCLUDED
#define PQS_TYPES_DERIVED_QUANTITY_AREA_HPP_INCLUDED

#include <pqs/types/base_quantity/length.hpp>

namespace pqs{
   
   constexpr inline auto abstract_area_v = pow<2>(abstract_length_v);

   using abstract_area_t = std::remove_cvref_t<decltype(abstract_area_v)>;
}

#endif // PQS_TYPES_DERIVED_QUANTITY_AREA_HPP_INCLUDED
