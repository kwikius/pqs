#ifndef PQS_DETAIL_CONVERSION_FACTOR_ADD_VALUES_HPP_INCLUDED
#define PQS_DETAIL_CONVERSION_FACTOR_ADD_VALUES_HPP_INCLUDED

#include <pqs/bits/std_ratio.hpp>
#include <pqs/bits/detail/ll_conversion_factor.hpp>

namespace pqs{ namespace detail{

   template <typename RatioLhs, typename RatioRhs>
   struct ll_conversion_factor_add_values{
      static_assert( std::ratio_equal<
         typename RatioLhs::exponent,typename RatioRhs::exponent
      >::value,"conversion_factor exponents must be same for add");
      typedef typename std::ratio_add< 
         typename RatioLhs::multiplier, typename RatioRhs::multiplier
      >::type result_ratio;

      typedef pqs::detail::ll_conversion_factor<result_ratio,typename RatioLhs::exponent> type;
   };
}}

#endif // PQS_DETAIL_CONVERSION_FACTOR_ADD_VALUES_HPP_INCLUDED
