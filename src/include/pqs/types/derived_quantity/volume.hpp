#ifndef PQS_TYPES_DERIVED_QUANTITY_VOLUME_HPP_INCLUDED
#define PQS_TYPES_DERIVED_QUANTITY_VOLUME_HPP_INCLUDED

#include <pqs/types/base_quantity/length.hpp>

namespace pqs{
   
   constexpr inline auto abstract_volume_v = pow<3>(abstract_length_v);

   using abstract_volume_t = std::remove_cvref_t<decltype(abstract_volume_v)>;
}

#endif // PQS_TYPES_DERIVED_QUANTITY_VOLUME_HPP_INCLUDED
