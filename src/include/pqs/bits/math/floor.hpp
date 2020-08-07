#ifndef PQS_BITS_MATH_FLOOR_HPP_INCLUDED
#define PQS_BITS_MATH_FLOOR_HPP_INCLUDED

#include <pqs/concepts/quantity.hpp>
#include <cmath>

namespace pqs{

   template <quantity Q>
   inline constexpr 
   auto floor(Q const & q)
   {
      using std::floor;
      return Q{floor(get_numeric_value(q))};
   }
}
#endif // PQS_BITS_MATH_FLOOR_HPP_INCLUDED
