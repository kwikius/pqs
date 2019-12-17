#ifndef PQS_DETAIL_CONVERSION_FACTOR_ADD_VALUES_HPP_INCLUDED
#define PQS_DETAIL_CONVERSION_FACTOR_ADD_VALUES_HPP_INCLUDED

#include <pqs/bits/std_ratio.hpp>
#include <pqs/bits/conversion_factor_def.hpp>

namespace pqs{ namespace detail{

   template <typename RatioLhs, typename RatioRhs>
   struct conversion_factor_add_values{
      static_assert( RatioLhs::exp == RatioRhs::exp,"conversion_factor exponents must be same for add");
      typedef typename std::ratio_add< typename RatioLhs::ratio, typename RatioRhs::ratio>::type result_ratio;

      typedef pqs::conversion_factor<result_ratio,RatioLhs::exp> type;
   };
}}

#endif // PQS_DETAIL_CONVERSION_FACTOR_ADD_VALUES_HPP_INCLUDED
