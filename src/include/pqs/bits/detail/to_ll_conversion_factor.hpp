#ifndef PQS_BITS_DETAIL_TO_LL_CONVERSION_FACTOR_HPP_INCLUDED
#define PQS_BITS_DETAIL_TO_LL_CONVERSION_FACTOR_HPP_INCLUDED

#include <pqs/bits/detail/ll_conversion_factor.hpp>

namespace pqs { namespace detail {

   template <typename ConvFactor>
   struct to_ll_conversion_factor { 
      using type = ll_conversion_factor<
         typename ConvFactor::type::multiplier,
         typename ConvFactor::type::exponent::ratio
      >;
   };

}} 

#endif // PQS_BITS_DETAIL_TO_LL_CONVERSION_FACTOR_HPP_INCLUDED
