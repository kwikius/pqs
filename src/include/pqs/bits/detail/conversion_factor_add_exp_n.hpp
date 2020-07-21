#ifndef PQS_DETAIL_CONVERSION_FACTOR_ADD_EXP_N_HPP_INCLUDED
#define PQS_DETAIL_CONVERSION_FACTOR_ADD_EXP_N_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/std_ratio.hpp>
#include <pqs/bits/detail/ll_conversion_factor.hpp>
#include <pqs/bits/meta/eval_if.hpp>
#include <pqs/bits/meta/to_power.hpp>

namespace pqs{ namespace detail{

   template <typename LLConversionFactor, intmax_t N>
   struct ll_add_conversion_factor1 {
      static_assert(N >= 0);
      typedef pqs::meta::to_power<10,N> mux;
      typedef pqs::detail::ll_conversion_factor<
         typename std::ratio_multiply<
            typename LLConversionFactor::multiplier,std::ratio<1,mux::value> 
         >::type,
         typename std::ratio_add<
            typename LLConversionFactor::exponent,std::ratio<N> 
         >::type
      > type;
   };

   template <typename LLConversionFactor, intmax_t N>
   struct ll_sub_conversion_factor1 {
      static_assert(N >= 0);
      typedef pqs::meta::to_power<10,N> mux;
      typedef pqs::detail::ll_conversion_factor<
         typename std::ratio_multiply<
            typename LLConversionFactor::multiplier,std::ratio<mux::value,1> 
          >::type,
         typename std::ratio_subtract<
            typename LLConversionFactor::exponent, 
            std::ratio<N> 
         >::type
      > type;
   };

    // conversion_factor::exp -> conversion_factor::exp + n
    // but number represented has same value
   template <typename LLConversionFactor, intmax_t N>
   struct ll_conversion_factor_add_exp_n :
      pqs::meta::eval_if<
         std::integral_constant<bool,(N > 0)> 
            ,ll_add_conversion_factor1<LLConversionFactor,N>
         ,std::integral_constant<bool,(N < 0)>
            ,ll_sub_conversion_factor1<LLConversionFactor,-N>
         ,LLConversionFactor
      >{};

}} // pqs::meta::detail

#endif // PQS_DETAIL_CONVERSION_FACTOR_SHIFT_EXP_HPP_INCLUDED
