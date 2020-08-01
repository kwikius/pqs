#ifndef PQS_TYPES_DERIVED_QUANTITY_ACCELERATION_HPP_INCLUDED
#define PQS_TYPES_DERIVED_QUANTITY_ACCELERATION_HPP_INCLUDED

#include <pqs/types/derived_quantity/speed.hpp>
#include <pqs/types/base_quantity/time.hpp>

namespace pqs{
   
   constexpr inline auto abstract_acceleration_v = abstract_speed_v / abstract_time_v;
   using abstract_acceleration_t = std::remove_cvref_t<decltype(abstract_acceleration_v)>;
}

#endif // PQS_TYPES_DERIVED_QUANTITY_ACCELERATION_HPP_INCLUDED
