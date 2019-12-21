#ifndef PQS_CONVERSION_FACTOR_DEF_HPP_INCLUDED
#define PQS_CONVERSION_FACTOR_DEF_HPP_INCLUDED

#include <pqs/bits/std_ratio.hpp>
#include <type_traits>

namespace pqs{ 

   namespace meta{

      template <typename T> 
      struct is_conversion_factor : std::false_type{};

   }

   // Mulriplier and exponent are compile time rationals
   template < typename Multiplier, typename  Exponent>
   struct conversion_factor{
      typedef typename Multiplier::type multiplier;
      typedef typename Exponent::type exponent;
     // TODO make 0 special case?
     // static_assert(ratio::num != 0, "only non-zero ratios values allowed");
      typedef conversion_factor<multiplier,exponent> type;
   };

   namespace meta{

      template <intmax_t MuxNum, intmax_t MuxDenom, intmax_t ExpNum, intmax_t ExpDenom>
      struct is_conversion_factor<
         pqs::conversion_factor<
            std::ratio<MuxNum,MuxDenom>,
            std::ratio<ExpNum,ExpDenom> 
         >
      > : std::true_type{};

   }

}  // pqs

#endif // PQS_CONVERSION_FACTOR_DEF_HPP_INCLUDED
