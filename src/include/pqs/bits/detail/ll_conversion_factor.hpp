#ifndef PQS_BITS_DETAIL_LL_CONV_FACTOR_HPP_INCLUDED
#define PQS_BITS_DETAIL_LL_CONV_FACTOR_HPP_INCLUDED

namespace pqs{ namespace detail {

   template <typename Multiplier, typename Exponent>
   struct ll_conversion_factor{
      typedef typename Multiplier::type multiplier;
      typedef typename Exponent::type exponent;
      static_assert(Multiplier::num != 0, "conversion_factor : only non-zero ratios values allowed");
      typedef ll_conversion_factor<multiplier,exponent> type;
   };

}}


#endif // PQS_BITS_DETAIL_LL_CONV_FACTOR_HPP_INCLUDED
