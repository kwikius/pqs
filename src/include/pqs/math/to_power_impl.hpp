#ifndef PQS_MATH_TO_POWER_IMPL_HPP_INCLUDED
#define PQS_MATH_TO_POWER_IMPL_HPP_INCLUDED

#include <cstdint>
#include <type_traits>

namespace pqs{
   
   namespace impl{

      template <int64_t N, typename Float>
      constexpr inline 
      typename std::enable_if<std::is_floating_point<Float>::value, Float>::type
      to_positive_power_impl(Float const & v)
      {
         static_assert(N > 0, "positive values of N only");
         return v * to_positive_power_impl<N-1>(v);
      }

      template <>
      constexpr inline long double to_positive_power_impl<0,long double>(long double const & v)
      {
        return 1.0L;
      }

      template <>
      constexpr inline double to_positive_power_impl<0,double>(double const & v)
      {
        return 1.0;
      }

      template <>
      constexpr inline float to_positive_power_impl<0,float>(float const & v)
      {
        return 1.f;
      }

      template <int64_t N, typename Float>
      constexpr inline 
      typename std::enable_if<std::is_floating_point<Float>::value, Float>::type
      to_negative_power_impl(Float const & v)
      {
        static_assert(N <= 0, "negative or zero values of N only");
        return 1/to_positive_power_impl<-N>(v);
      }

      template <int64_t N, typename Float>
      constexpr inline 
      typename std::enable_if<(N >=0) && std::is_floating_point<Float>::value, Float>::type
      to_power_impl(Float const & v)
      {
         return to_positive_power_impl<N>(v);
      }

      template <int64_t N, typename Float> 
      constexpr inline
      typename std::enable_if< (N < 0) && std::is_floating_point<Float>::value, Float>::type
      to_power_impl(Float const & v)
      {
         return to_negative_power_impl<N>(v);
      }

   } // impl

}// pqs

#endif // PQS_MATH_TO_POWER_IMPL_HPP_INCLUDED
