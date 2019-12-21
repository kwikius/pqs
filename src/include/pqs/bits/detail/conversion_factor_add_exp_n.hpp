#ifndef PQS_DETAIL_CONVERSION_FACTOR_ADD_EXP_N_HPP_INCLUDED
#define PQS_DETAIL_CONVERSION_FACTOR_ADD_EXP_N_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/bits/conversion_factor_def.hpp>
#include <pqs/meta/eval_if.hpp>
#include <pqs/meta/to_power.hpp>

namespace pqs{ namespace detail{

   template <typename RatioExp, intmax_t N>
   struct add_conversion_factor1 {
      static_assert(N >= 0);
      typedef pqs::meta::to_power<10,N> mux;

      typedef conversion_factor<
         typename std::ratio_multiply<
            typename RatioExp::multiplier,std::ratio<1,mux::value> 
         >::type,
         typename std::ratio_add<
            typename RatioExp::exponent,std::ratio<N> 
         >::type
      > type;
   };

   template <typename RatioExp, intmax_t N>
   struct sub_conversion_factor1 {
      static_assert(N >= 0);
      typedef pqs::meta::to_power<10,N> mux;
      typedef conversion_factor<
         typename std::ratio_multiply<
            typename RatioExp::multiplier,std::ratio<mux::value,1> 
          >::type,
         typename std::ratio_subtract<
            typename RatioExp::exponent, 
            std::ratio<N> 
         >::type
      > type;
   };

    // conversion_factor::exp -> conversion_factor::exp + n
    // but number represented has same value
   template <typename RatioExp, intmax_t N>
   struct conversion_factor_add_exp_n :
      pqs::meta::eval_if<
         std::integral_constant<bool,(N > 0)> 
            ,add_conversion_factor1<RatioExp,N>
         ,std::integral_constant<bool,(N < 0)>
            ,sub_conversion_factor1<RatioExp,-N>
         ,RatioExp
      >{};

}} // pqs::meta::detail

#endif // PQS_DETAIL_CONVERSION_FACTOR_SHIFT_EXP_HPP_INCLUDED
