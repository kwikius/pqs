
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

   template <>
   struct fixed_string_to_power<pqs::charset_utf8>{

      template <int N>
      static constexpr auto apply()
      {
         if constexpr ( N > 0)
            return superscript<N>;
         else
            return superscript_minus + superscript<-N>;
      }
   };


   template <>
   struct fixed_string_to_power<pqs::charset_ascii>{
      template <int N>
      static constexpr auto apply()
      {
         return to_fixed_string_ascii<N>();
      }
   };

   template <pqs::base_quantity Qb, int exp10,int extent, typename CharSet>
   constexpr auto get_base_unit_expression()
   {
     // N.B for multi base exp dimes ,
     // should probably just put exp10 at end
      auto constexpr no_ext_str = 
         pqs::unit_symbol_prefix<
            exp10/extent + pqs::si::get_base_unit_prefix_offset<Qb> 
            ,CharSet
         > +
         pqs::get_base_unit_symbol<
            Qb,pqs::si_measurement_system,CharSet
         >;
      if constexpr ( extent == 1)
         return no_ext_str;
      else
         return no_ext_str + fixed_string_to_power<CharSet>::template apply<extent>();      
   }
}

#if defined PQS_STANDALONE
int errors =0;
int main()
#else
void sandbox()
#endif
{
   using base_quantity = pqs::base_time;
  // requires 
   constexpr int exp10 = 3;
   constexpr int extent = -1;
   using charset = pqs::charset_utf8;
 ///  using charset = pqs::charset_ascii;
   auto constexpr x = get_base_unit_expression<base_quantity,exp10,extent,charset>();

   std::cout << x <<'\n';
}
