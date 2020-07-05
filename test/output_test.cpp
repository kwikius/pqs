
#include "test.hpp"
#include <pqs/concepts/dimension.hpp>
#include <pqs/si/measurement_system.hpp>
#include <pqs/bits/abs.hpp>
#include <string>

/**
 * @ brief output a base_dimension_exponent.
 *   requires 
 * a base_dimension_exponent
 * a measurement system
 * an output character type
 */

namespace {

// Acknowledgement to
// https://github.com/mpusz/units/blob/master/src/include/units/bits/external/text_tools.h
// which is 
// The MIT License (MIT)
//
// Copyright (c) 2018 Mateusz Pusz
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

   template <int N>
   constexpr auto to_fixed_string_ascii()
   {
      if constexpr ( N < 0)
         return pqs::basic_fixed_string{"-"} + to_fixed_string_ascii<-N>();
      else if constexpr (N < 10)
         return pqs::basic_fixed_string{static_cast<char>( N + '0')};
      else
         return to_fixed_string_ascii<N/10>() + to_fixed_string_ascii<N%10>();
   }

   template <typename Charset>
   struct fixed_string_to_power;

   template<int Value>
     requires (0 <= Value) && (Value < 10)
   static constexpr pqs::basic_fixed_string superscript = "";

   template<> inline constexpr pqs::basic_fixed_string superscript<0> = "\u2070";
   template<> inline constexpr pqs::basic_fixed_string superscript<1> = "\u00b9";
   template<> inline constexpr pqs::basic_fixed_string superscript<2> = "\u00b2";
   template<> inline constexpr pqs::basic_fixed_string superscript<3> = "\u00b3";
   template<> inline constexpr pqs::basic_fixed_string superscript<4> = "\u2074";
   template<> inline constexpr pqs::basic_fixed_string superscript<5> = "\u2075";
   template<> inline constexpr pqs::basic_fixed_string superscript<6> = "\u2076";
   template<> inline constexpr pqs::basic_fixed_string superscript<7> = "\u2077";
   template<> inline constexpr pqs::basic_fixed_string superscript<8> = "\u2078";
   template<> inline constexpr pqs::basic_fixed_string superscript<9> = "\u2079";

   inline constexpr pqs::basic_fixed_string superscript_minus = "\u207b";
   inline constexpr pqs::basic_fixed_string solidus = "\u2044";
   inline constexpr pqs::basic_fixed_string fraction_slash = "\u002F";

   template <int N>
   constexpr auto to_fixed_string_utf8()
   {
      if constexpr ( N < 0)
         return superscript_minus + to_fixed_string_utf8<-N>();
      else if constexpr (N < 10)
         return superscript<N>;
      else
         return to_fixed_string_utf8<N/10>() + to_fixed_string_utf8<N%10>();
   }

   template <typename Exp>
   inline constexpr auto to_fixed_string_fractional_power_utf8()
   {
      return to_fixed_string_utf8<Exp::num>()
               + fraction_slash
               + to_fixed_string_utf8<Exp::den>();
   }

   template <typename Exp>
   inline constexpr auto to_fixed_string_signed_fractional_power_utf8()
   {
      if constexpr ( Exp::num > 0)
         return to_fixed_string_fractional_power_utf8<Exp>();
      else
         return superscript_minus + to_fixed_string_fractional_power_utf8<
            std::ratio_multiply<Exp,std::ratio<-1> > 
         >();
   }

   template <>
   inline constexpr auto to_fixed_string_fractional_power_utf8<std::ratio<1,2> >()
   {
      return pqs::basic_fixed_string{"\u00bd"};
   }

   template <>
   inline constexpr auto to_fixed_string_fractional_power_utf8<std::ratio<1,3> >()
   {
      return pqs::basic_fixed_string{"\u2153"};
   }

   template <>
   inline constexpr auto to_fixed_string_fractional_power_utf8<std::ratio<1,4> >()
   {
      return pqs::basic_fixed_string{"\u00bc"};
   }


   template <>
   inline constexpr auto to_fixed_string_fractional_power_utf8<std::ratio<1,5> >()
   {
      return pqs::basic_fixed_string{"\u2155"};
   }

   template <>
   inline constexpr auto to_fixed_string_fractional_power_utf8<std::ratio<2,3> >()
   {
      return pqs::basic_fixed_string{"\u2154"};
   }

   template <>
   inline constexpr auto to_fixed_string_fractional_power_utf8<std::ratio<3,4> >()
   {
      return pqs::basic_fixed_string{"\u00be"};
   }

   template <>
   struct fixed_string_to_power<pqs::charset_utf8>{

      template <typename Exp>
      static constexpr auto apply()
      {
         if constexpr ( Exp::den == 1)
            return to_fixed_string_utf8<Exp::num>();
         else 
            return to_fixed_string_signed_fractional_power_utf8<Exp>();
      }
   };


   template <>
   struct fixed_string_to_power<pqs::charset_ascii>{
      template <typename Exp>
      static constexpr auto apply()
      {
         if constexpr (Exp::den == 1)
           return to_fixed_string_ascii<Exp::num>();
         else 
            return to_fixed_string_ascii<Exp::num>()
               + pqs::basic_fixed_string{'/'}
               + to_fixed_string_ascii<Exp::den>();
      }
   };

   template <pqs::base_quantity Qb, typename Exp, typename CharSet>
   constexpr auto get_base_unit_expression()
   {
      auto constexpr no_ext_str = 
         pqs::unit_symbol_prefix<
           pqs::si::get_base_unit_prefix_offset<Qb> 
            ,CharSet
         > +
         pqs::get_base_unit_symbol<
            Qb,pqs::si_measurement_system,CharSet
         >;
      if constexpr ( std::ratio_equal<Exp,std::ratio<1> >::value )
         return no_ext_str;
      else
         return no_ext_str + fixed_string_to_power<CharSet>::template apply<Exp>();      
   }
}

#if defined PQS_STANDALONE
int errors =0;
int main()
#else
void sandbox()
#endif
{
   using base_quantity = pqs::base_mass;

   using exp = std::ratio<-3>;
 #if 1
   using charset = pqs::charset_utf8;
 #else
   using charset = pqs::charset_ascii;
 #endif
   auto constexpr x = get_base_unit_expression<base_quantity,exp,charset>();

   std::cout << x <<'\n';
}
