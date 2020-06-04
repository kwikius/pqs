#ifndef PQS_MATH_RATIO_ROOT_HPP_INCLUDED
#define PQS_MATH_RATIO_ROOT_HPP_INCLUDED

#include <limits>
#include <ratio>
#include <type_traits>
//#include <cmath>
#include <pqs/math/to_power_impl.hpp>

#erro TODO

namespace pqs{ namespace impl{

      template <int N
      struct root_impl{
         static_assert(N > 0,"positive root only");
/*
         template <typename Float>
         constexpr
         typename std::enable_if<std::is_floating_point<Float>::value, Float>::type
         operator() (Float const & v)const
         {
            return apply(v, 0, v/N);
         }
*/
         template <typename Ratio>
         struct eval{
             typedef typename apply<Ratio,0,Ratio>::type type;
         };
      private:
/*
         template <typename Float>
         static constexpr 
         typename std::enable_if< std::is_floating_point<Float>::value, Float>::type
         approx(Float const & v, int const & iter , Float const & prev_approx)
         {
            
            return ( (N-1) * prev_approx + v * to_negative_power_impl<1-N>(prev_approx) )/ N;
         }
*/
         template <typename RatioV, int Iter, typename RatioPrevApprox>
         struct approx{
             typedef typename ratio_to_negative_power<1-N,RatioPrevApprox>::type v1;
             typedef typename std::ratio_multiply<RatioV,v1>::type v2;
             typedef typename std::ratio_multiply< std::ratio<N-1> , RatioPrevApprox>::type v3;
             typedef typename std::ratio_add<v2,v3>::type v4;
             typedef typename std::ratio_divide<v4,std::ratio<N> >::type type;
       
         };
         template <typename Float>
         static constexpr 
         typename std::enable_if< std::is_floating_point<Float>::value, Float>::type
         apply (Float const & v,int const & iter,Float const& prev_approx )
         {
            return (std::abs( approx(v,iter,prev_approx) - prev_approx ) <= std::numeric_limits<Float>::epsilon()) 
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
      return impl::root_impl<N>{}(v);
   }
}// pqs

#endif // PQS_MATH_RATIO_ROOT_HPP_INCLUDED
