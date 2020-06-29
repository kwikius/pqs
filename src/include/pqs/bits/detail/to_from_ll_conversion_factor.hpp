#ifndef PQS_BITS_DETAIL_TO_FROM_LL_CONVERSION_FACTOR_HPP_INCLUDED
#define PQS_BITS_DETAIL_TO_FROM_LL_CONVERSION_FACTOR_HPP_INCLUDED

#include <pqs/bits/conversion_factor_def.hpp>
#include <pqs/bits/detail/ll_conversion_factor.hpp>
#include <pqs/type_templates/exponent10_fwd.hpp>

namespace pqs { namespace detail {

   template <typename ConvFactor>
   struct to_ll_conversion_factor { 
      using type = ll_conversion_factor<
         typename ConvFactor::type::multiplier,
         typename ConvFactor::type::exponent::ratio
      >;
   };

   template <typename LLConvFactor>
   struct to_conversion_factor { 
      using type = pqs::conversion_factor<
         typename LLConvFactor::multiplier,
         pqs::exponent10<
            LLConvFactor::type::exponent::num,
            LLConvFactor::type::exponent::den
         >
      >;
   };
}}

#endif // PQS_BITS_DETAIL_TO_FROM_LL_CONVERSION_FACTOR_HPP_INCLUDED
