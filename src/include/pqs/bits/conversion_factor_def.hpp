#ifndef PQS_CONVERSION_FACTOR_DEF_HPP_INCLUDED
#define PQS_CONVERSION_FACTOR_DEF_HPP_INCLUDED

#include <pqs/bits/conversion_factor_ops.hpp>
#include <pqs/bits/conversion_factor_fwd.hpp>

namespace pqs{ 

   template <typename Multiplier, typename  Exponent>
   struct conversion_factor{
      typedef typename Multiplier::type multiplier;
      typedef typename Exponent::type exponent;
     // TODO make 0 special case?
      static_assert(Multiplier::num != 0, "conversion_factor : only non-zero ratios values allowed");
      typedef conversion_factor<multiplier,exponent> type;
   };

   template <
      typename Multiplier, typename  Exponent, 
      intmax_t N1, intmax_t D1
   > 
   inline constexpr
   auto operator * ( conversion_factor<Multiplier,Exponent>, std::ratio<N1,D1> )
   {
      using cf = typename conversion_factor<Multiplier,Exponent>::type;
      using multiplier = typename cf::multiplier;
      return typename pqs::conversion_factor_normalise<
         pqs::conversion_factor<
            std::ratio_multiply<multiplier,std::ratio<N1,D1> >,
            Exponent
         >
      >::type{};
   }

   namespace impl{

      template <intmax_t MuxNum, intmax_t MuxDenom, typename UnitExp>
      struct is_conversion_factor_impl<
         pqs::conversion_factor<
            std::ratio<MuxNum,MuxDenom>,
            UnitExp 
         >
      > : std::true_type{};

      template <intmax_t MuxNum, intmax_t MuxDenom, typename UnitExp>
      struct get_exponent_impl<
        pqs::conversion_factor<
            std::ratio<MuxNum,MuxDenom>,
            UnitExp 
         >
      > {
         typedef typename  pqs::conversion_factor<
            std::ratio<MuxNum,MuxDenom>,
            UnitExp 
         >::exponent type;
      };

   } //impl

}  // pqs

#endif // PQS_CONVERSION_FACTOR_DEF_HPP_INCLUDED
