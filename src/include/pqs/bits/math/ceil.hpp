#ifndef PQS_BITS_MATH_CEIL_HPP_INCLUDED
#define PQS_BITS_MATH_CEIL_HPP_INCLUDED

#include <pqs/concepts/quantity.hpp>
#include <cmath>

namespace pqs{

   template <quantity Q>
   inline constexpr 
   auto ceil(Q const & q)
   {
      using std::ceil;
      return Q{ceil(get_numeric_value(q))};
   }
}
#endif // PQS_BITS_MATH_CEIL_HPP_INCLUDED
