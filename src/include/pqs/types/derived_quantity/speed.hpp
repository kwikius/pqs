#ifndef PQS_TYPES_DERIVED_QUANTITY_SPEED_HPP_INCLUDED
#define PQS_TYPES_DERIVED_QUANTITY_SPEED_HPP_INCLUDED

#include <pqs/types/base_quantity/length.hpp>
#include <pqs/types/base_quantity/time.hpp>

namespace pqs{
   
   constexpr inline auto abstract_speed_v = abstract_length<> / abstract_time<>;

   using abstract_speed_t = std::remove_cvref_t<decltype(abstract_speed_v)>;
}

#endif // PQS_TYPES_DERIVED_QUANTITY_SPEED_HPP_INCLUDED
