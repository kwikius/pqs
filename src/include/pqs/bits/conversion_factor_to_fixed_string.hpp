#ifndef PQS_BITS_CONVERSION_FACTOR_TO_FIXED_STRING_HPP_INCLUDED
#define PQS_BITS_CONVERSION_FACTOR_TO_FIXED_STRING_HPP_INCLUDED

#include <pqs/bits/conversion_factor_def.hpp>
#include <pqs/type_templates/exponent10.hpp>
#include <ratio>
#include <pqs/bits/fixed_string_charset_stuff.hpp>

namespace pqs{

   namespace detail {

      template <typename CharSet>
      inline constexpr basic_fixed_string 
      superscript_left_brace= "(";
      template <>
      inline constexpr basic_fixed_string 
      superscript_left_brace<charset_utf8> = "\u207d";

      template <typename CharSet>
      inline constexpr basic_fixed_string 
      superscript_right_brace= ")";

      template <>
      inline constexpr basic_fixed_string 
      superscript_right_brace<charset_utf8> = "\u207e"; 

      template< typename R, typename CharSet>
      inline constexpr 
      auto opt_braced_number_to_regular_fixed_string()
      {
         if constexpr( R::den == 1)
            return to_regular_fixed_string<R,CharSet>();
         else
            return basic_fixed_string("(") +
               to_regular_fixed_string<R,CharSet>() +
               basic_fixed_string{")"};
      }

      template< typename R, typename CharSet>
      inline constexpr 
      auto opt_braced_number_to_superscript_fixed_string()
      {
         if constexpr( R::den == 1)
            return to_superscript_fixed_string<R,CharSet>();
         else

            return superscript_left_brace<CharSet> +
               to_superscript_fixed_string<R,CharSet>() +
               superscript_right_brace<CharSet>;
      }

      template< typename R, typename Charset>
         requires  std::is_same_v<Charset,charset_utf8>
      inline constexpr 
      auto opt_braced_number_to_superscript_fixed_string()
      {
          return to_superscript_fixed_string<R,charset_utf8>();
      }

      template <typename CharSet>
      inline constexpr basic_fixed_string ten_to_pow = "*10^";

      template<>
      inline constexpr basic_fixed_string ten_to_pow<charset_utf8> 
         = multiplication_dot<charset_utf8> + basic_fixed_string("10");

   } // detail
   
   template <
      typename Cf,
      typename CharSet
   >
      requires is_conversion_factor<Cf>
   inline constexpr 
   auto conversion_factor_to_fixed_string()
   {
      using e = typename Cf::exponent::ratio;
      using m  = typename Cf::multiplier;
     //return basic_fixed_string("Wahey");
      if constexpr ( std::ratio_equal<e,std::ratio<0> >::value)
         
         return pqs::detail::opt_braced_number_to_regular_fixed_string<m,CharSet>();
      else
         return pqs::detail::opt_braced_number_to_regular_fixed_string<m,CharSet>() +
            pqs::detail::ten_to_pow<CharSet> +
               pqs::detail::opt_braced_number_to_superscript_fixed_string<e,CharSet>();
   }
}

#endif // PQS_BITS_CONVERSION_FACTOR_TO_FIXED_STRING_HPP_INCLUDED
