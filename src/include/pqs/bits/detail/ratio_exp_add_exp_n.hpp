#ifndef PQS_DETAIL_RATIO_EXP_ADD_EXP_N_HPP_INCLUDED
#define PQS_DETAIL_RATIO_EXP_ADD_EXP_N_HPP_INCLUDED

#include <type_traits>
#include <pqs/bits/ratio_exp_def.hpp>
#include <pqs/meta/eval_if.hpp>
#include <pqs/meta/to_power.hpp>

namespace pqs{ namespace detail{

   template <typename RatioExp, intmax_t N>
   struct add_ratio_exp1 {
       static_assert(N >= 0);
       typedef pqs::meta::to_power<10,N> mux;

       typedef ratio_exp<
          typename std::ratio_multiply<
             typename RatioExp::ratio,std::ratio<1,mux::value> 
          >::type
          ,RatioExp::exp + N
       > type;
   };

   template <typename RatioExp, intmax_t N>
   struct sub_ratio_exp1 {
       static_assert(N >= 0);
       typedef pqs::meta::to_power<10,N> mux;
       typedef ratio_exp<
          typename std::ratio_multiply<
             typename RatioExp::ratio,std::ratio<mux::value,1> 
          >::type
          ,RatioExp::exp - N
       > type;
   };

    // ratio_exp::exp -> ratio_exp::exp + n
    // but number represented has same value
   template <typename RatioExp, intmax_t N>
   struct ratio_exp_add_exp_n :
      pqs::meta::eval_if<
         std::bool_constant<(N > 0)> 
            ,add_ratio_exp1<RatioExp,N>
         ,std::bool_constant<(N < 0)>
            ,sub_ratio_exp1<RatioExp,-N>
         ,RatioExp
      >{};

}} // pqs::meta::detail

#endif // PQS_DETAIL_RATIO_EXP_SHIFT_EXP_HPP_INCLUDED
