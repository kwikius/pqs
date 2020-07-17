#ifndef PQS_MATH_RATIO_ROOT_HPP_INCLUDED
#define PQS_MATH_RATIO_ROOT_HPP_INCLUDED

//#include <limits>
//#include <ratio>
#include <type_traits>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/bits/math/fn_to_power_impl.hpp>

//#error TODO
//This is pretty unstable

namespace pqs{ 

      template <int N, typename Ratio>
      struct ratio_to_positive_power;

      template <typename Ratio>
      struct ratio_to_positive_power<0,Ratio>{
         using type = std::ratio<1>;
      };

      template <typename Ratio>
      struct ratio_to_positive_power<1,Ratio>{
         using type = typename Ratio::type;
      };

      template <int N, typename Ratio>
      struct ratio_to_positive_power{
          using type = std::ratio_multiply<Ratio,typename ratio_to_positive_power<N-1,Ratio>::type>;
      };

      template <int N, typename Ratio>
      struct ratio_to_negative_power{
         static_assert( N <=0,"negative or 0 only");
          using type = std::ratio_divide<
               std::ratio<1>,
               typename ratio_to_positive_power<-N,Ratio>::type
            >;
      };

     

    namespace impl{

      template <int N>
      struct ratio_root_impl{
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
             using v1 = typename ratio_to_negative_power<1-N,RatioPrevApprox>::type;
             using v2 = std::ratio_multiply<RatioV,v1>;
             using v3 = std::ratio_multiply<std::ratio<N-1> , RatioPrevApprox>;
             using v4 = std::ratio_add<v2,v3>;
             using type = std::ratio_divide<v4,std::ratio<N> >;
       
         };
         
         template <typename RatioV,int Iter,typename RPrevApprox>
         struct apply{
            using cur_approx = typename approx<RatioV,Iter,RPrevApprox>::type ;
            using approx_diff = std::ratio_subtract<cur_approx,RPrevApprox>;
            using abs_approx_diff = typename pqs::detail::std_ratio_abs< approx_diff>::type; 
            using type = pqs::meta::eval_if< 
               std::ratio_equal<abs_approx_diff,std::ratio<1,20000000> >,
               cur_approx,
               apply<RatioV,Iter + 1,cur_approx>
            >::type;
         };

         template <typename Ratio>
         struct eval{
             typedef typename apply<Ratio,0,std::ratio_divide<Ratio,std::ratio<N> > >::type type;
         };
#if 0
         template <typename Float>
         static constexpr 
         typename std::enable_if< std::is_floating_point<Float>::value, Float>::type
         apply (Float const & v,int const & iter,Float const& prev_approx )
         {
            return (std::abs( approx(v,iter,prev_approx) - prev_approx ) <= std::numeric_limits<Float>::epsilon()) 
               ? approx(v,iter,prev_approx)
               : apply(v,iter+1, approx(v,iter,prev_approx));
         }
#endif
      };

   } // impl

}// pqs

#endif // PQS_MATH_RATIO_ROOT_HPP_INCLUDED
