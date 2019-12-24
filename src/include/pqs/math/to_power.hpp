#ifndef PQS_MATH_TO_POWER_HPP_INCLUDED
#define PQS_MATH_TO_POWER_HPP_INCLUDED

#include <pqs/math/to_power_impl.hpp>
#include <pqs/math/root.hpp>

namespace pqs{

   template <int64_t N, typename Float>
   constexpr inline
   typename std::enable_if< std::is_floating_point<Float>::value, Float>::type
   to_power(Float const & v)
   {
      return impl::to_power_impl<N>(v);
   }

   template <int N, int D, typename Float>
   inline constexpr
   typename std::enable_if< ( N !=1) && (D > 1) && std::is_floating_point<Float>::value, Float>::type
   to_power( Float const & v)
   {
      return pqs::root<D>(pqs::to_power<N>(v));
   }

   template <int N, int D, typename Float>
   inline constexpr
   typename std::enable_if< ( N ==1) && (D > 1) && std::is_floating_point<Float>::value, Float>::type
   to_power( Float const & v)
   {
      return pqs::root<D>(v);
   }

   template <int N, int D, typename Float>
   inline constexpr
   typename std::enable_if< (N == 1) &&(D==1) && std::is_floating_point<Float>::value, Float>::type
   to_power( Float const & v)
   {
      return v;
   }

   template <int N, int D, typename Float>
   inline constexpr
   typename std::enable_if< (N !=1) && (D == 1) && std::is_floating_point<Float>::value, Float>::type
   to_power( Float const & v)
   {
      return pqs::to_power<N>(v);
   }

} // pqs

#endif // PQS_MATH_TO_POWER_HPP_INCLUDED
