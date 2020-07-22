#ifndef PQS_SI_GET_BASE_UNIT_PREFIX_OFFSET_HPP_INCLUDED
#define PQS_SI_GET_BASE_UNIT_PREFIX_OFFSET_HPP_INCLUDED

#include <pqs/concepts/base_quantity.hpp>

namespace pqs{ namespace si{

   template <base_quantity Q>
   inline constexpr int get_base_unit_prefix_offset = 0;

}} //pqs::si

#endif // PQS_SI_GET_BASE_UNIT_PREFIX_OFFSET_HPP_INCLUDED
