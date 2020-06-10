#ifndef PQS_MATH_ROOT_HPP_INCLUDED
#define PQS_MATH_ROOT_HPP_INCLUDED

#include <limits>
#include <cmath>
#include <pqs/math/fn_to_power_impl.hpp>

namespace pqs{ namespace impl{

      template <int N>
      struct root_impl{
         static_assert(N > 0,"positive root only");

         template <typename Float>
         static constexpr
         typename std::enable_if<std::is_floating_point<Float>::value, Float>::type
         apply(Float const & v)
         {
            return apply(v, 0, v/N);
         }
      private:
         template <typename Float>
         static constexpr 
         typename std::enable_if< std::is_floating_point<Float>::value, Float>::type
         approx(Float const & v, int const & iter , Float const & prev_approx)
         {
            return ( (N-1) * prev_approx + v * fn_to_negative_power_impl<1-N>(prev_approx) )/ N;
         }

         template <typename Float>
         static constexpr Float do_abs( Float const & v)
         {
            return (v >= Float{0}) ? v : -v;
         }

         template <typename Float>
         static constexpr 
         typename std::enable_if< std::is_floating_point<Float>::value, Float>::type
         apply (Float const & v,int const & iter,Float const& prev_approx )
         {
            return (do_abs( approx(v,iter,prev_approx) - prev_approx ) <= std::numeric_limits<Float>::epsilon()) 
               ? approx(v,iter,prev_approx)
               : apply(v,iter+1, approx(v,iter,prev_approx));
         }
      };

   } // impl

   template <int N, typename Float>
   constexpr inline 
   typename std::enable_if< std::is_floating_point<Float>::value, Float>::type
   root (Float const & v)
   {
      return impl::root_impl<N>::apply(v);
   }
}// pqs

#endif // PQS_MATH_ROOT_HPP_INCLUDED
