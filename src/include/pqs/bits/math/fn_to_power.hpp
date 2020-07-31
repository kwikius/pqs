#ifndef PQS_MATH_FN_TO_POWER_HPP_INCLUDED
#define PQS_MATH_FN_TO_POWER_HPP_INCLUDED

#include <pqs/bits/math/fn_to_power_impl.hpp>
#include <pqs/bits/math/root.hpp>

namespace pqs{

   template <int64_t N, typename Float>
       requires std::is_floating_point_v<Float>
   constexpr inline
  // typename std::enable_if< std::is_floating_point<Float>::value, Float>::type
  
   auto fn_to_power(Float const & v)
   {
      return impl::fn_to_power_impl<N>(v);
   }

   template <int N, int D, typename Float>
      requires std::is_floating_point_v<Float> && ( N !=1) && (D > 1) 
   inline constexpr
  // typename std::enable_if< ( N !=1) && (D > 1) && std::is_floating_point<Float>::value, Float>::type
   auto fn_to_power( Float const & v)
   {
      return pqs::root<D>(pqs::fn_to_power<N>(v));
   }

   template <int N, int D, typename Float>
      requires std::is_floating_point_v<Float> && ( N ==1) && (D > 1) 
   inline constexpr
  // typename std::enable_if< ( N ==1) && (D > 1) && std::is_floating_point<Float>::value, Float>::type
   auto fn_to_power( Float const & v)
   {
      return pqs::root<D>(v);
   }

   template <int N, int D, typename Float>
      requires std::is_floating_point_v<Float> && ( N ==1) && (D == 1) 
   inline constexpr
  // typename std::enable_if< (N == 1) &&(D==1) && std::is_floating_point<Float>::value, Float>::type
   auto fn_to_power( Float const & v)
   {
      return v;
   }

   template <int N, int D, typename Float>
      requires std::is_floating_point_v<Float> && ( N !=1) && (D == 1) 
   inline constexpr
  // typename std::enable_if< (N !=1) && (D == 1) && std::is_floating_point<Float>::value, Float>::type
   auto fn_to_power( Float const & v)
   {
      return pqs::fn_to_power<N>(v);
   }

} // pqs

#endif // PQS_MATH_FN_TO_POWER_HPP_INCLUDED
