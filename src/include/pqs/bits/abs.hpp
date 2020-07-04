#ifndef PQS_BITS_ABS_HPP_INCLUDED
#define PQS_BITS_ABS_HPP_INCLUDED

#include <type_traits>

namespace pqs{

   template<typename T>
       requires std::is_arithmetic_v<T>
   constexpr inline
   T abs(T const & in)
   {
      return (in >= T{0}) ? in:-in;
   }
}

#endif // PQS_BITS_ABS_HPP_INCLUDED
