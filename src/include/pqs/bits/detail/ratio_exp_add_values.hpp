#ifndef PQS_DETAIL_RATIO_EXP_ADD_VALUES_HPP_INCLUDED
#define PQS_DETAIL_RATIO_EXP_ADD_VALUES_HPP_INCLUDED

#include <ratio>

#include <pqs/bits/ratio_exp_def.hpp>

namespace pqs{ namespace detail{

   template <typename RatioLhs, typename RatioRhs>
   struct ratio_exp_add_values{
      static_assert( RatioLhs::exp == RatioRhs::exp,"ratio_exp exponents must be same for add");
      typedef typename std::ratio_add< typename RatioLhs::ratio, typename RatioRhs::ratio>::type result_ratio;

      typedef pqs::ratio_exp<result_ratio,RatioLhs::exp> type;
   };
}}

#endif // PQS_DETAIL_RATIO_EXP_ADD_VALUES_HPP_INCLUDED
