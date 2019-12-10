#ifndef PQS_META_RATIO_EXP_ADD_EXP_N_HPP_INCLUDED
#define PQS_META_RATIO_EXP_ADD_EXP_N_HPP_INCLUDED

#include <type_traits>
#include <pqs/meta/ratio_exp_def.hpp>
#include <pqs/meta/eval_if.hpp>

namespace pqs{ namespace meta{ namespace detail{

   template <intmax_t Val, intmax_t Exp>
   struct to_power{
      typedef to_power type;
      static_assert( ( Val > 0 ) && (Exp > 0 ) ,"unexpected negative values");
      static constexpr uintmax_t value = Val * to_power<Val,Exp-1>::value;
   };

   template <intmax_t Val>
   struct to_power<Val,0> {  
      
      typedef to_power type;
      static constexpr intmax_t value = 1;
   };

   template <typename RatioExp, intmax_t N>
   struct add_ratio_exp1 {
       static_assert(N >= 0);
       typedef to_power<10,N> mux;

       typedef ratio_exp<
         typename std::ratio_multiply<
            typename RatioExp::ratio
            ,std::ratio<1,mux::value> 
         >::type
         ,RatioExp::exp + N
       > type;
   };

   template <typename RatioExp, intmax_t N>
   struct sub_ratio_exp1 {
       static_assert(N >= 0);
       typedef to_power<10,N> mux;
       typedef ratio_exp<
         typename std::ratio_multiply<
            typename RatioExp::ratio
            ,std::ratio<mux::value,1> 
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

}}} // pqs::meta::detail

#endif // PQS_META_RATIO_EXP_SHIFT_EXP_HPP_INCLUDED
