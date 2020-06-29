#ifndef PQS_CONVERSION_FACTOR_DEF_HPP_INCLUDED
#define PQS_CONVERSION_FACTOR_DEF_HPP_INCLUDED

#include <pqs/bits/std_ratio.hpp>
#include <pqs/type_templates/exponent10_fwd.hpp>
#include <pqs/type_functions/get_exponent.hpp>
#include <type_traits>

namespace pqs{ 

   template <typename Multiplier, typename  Exponent>
   struct conversion_factor{
      typedef typename Multiplier::type multiplier;
      typedef typename Exponent::type exponent;
     // TODO make 0 special case?
      static_assert(Multiplier::num != 0, "conversion_factor : only non-zero ratios values allowed");
      typedef conversion_factor<multiplier,exponent> type;
   };


   namespace impl{

      template <typename T, typename Where = void> 
      struct is_conversion_factor_impl : std::false_type{};

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

   template <typename T>
   struct is_conversion_factor_legacy : impl::is_conversion_factor_impl< 
      typename pqs::meta::strip_cr<T>::type
   >{};

   template  <typename T>
   inline constexpr bool is_conversion_factor = is_conversion_factor_legacy<T>::value;

  

}  // pqs

#endif // PQS_CONVERSION_FACTOR_DEF_HPP_INCLUDED
