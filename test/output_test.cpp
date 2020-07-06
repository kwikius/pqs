
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


   template<int N, typename CharSet>
     requires (N >=0 ) && (N < 10)
   inline constexpr pqs::basic_fixed_string exp_digit = static_cast<char>( N + '0');

   template<> inline constexpr pqs::basic_fixed_string exp_digit<0,pqs::charset_utf8> = "\u2070";
   template<> inline constexpr pqs::basic_fixed_string exp_digit<1,pqs::charset_utf8> = "\u00b9";
   template<> inline constexpr pqs::basic_fixed_string exp_digit<2,pqs::charset_utf8> = "\u00b2";
   template<> inline constexpr pqs::basic_fixed_string exp_digit<3,pqs::charset_utf8> = "\u00b3";
   template<> inline constexpr pqs::basic_fixed_string exp_digit<4,pqs::charset_utf8> = "\u2074";
   template<> inline constexpr pqs::basic_fixed_string exp_digit<5,pqs::charset_utf8> = "\u2075";
   template<> inline constexpr pqs::basic_fixed_string exp_digit<6,pqs::charset_utf8> = "\u2076";
   template<> inline constexpr pqs::basic_fixed_string exp_digit<7,pqs::charset_utf8> = "\u2077";
   template<> inline constexpr pqs::basic_fixed_string exp_digit<8,pqs::charset_utf8> = "\u2078";
   template<> inline constexpr pqs::basic_fixed_string exp_digit<9,pqs::charset_utf8> = "\u2079";

   template<typename CharSet>
   inline constexpr pqs::basic_fixed_string minus_sign = "-";

   template <>
   inline constexpr pqs::basic_fixed_string minus_sign<pqs::charset_utf8> = "\u207b";

   template<typename CharSet>
   inline constexpr pqs::basic_fixed_string fraction_slash = "/";
   
   template <>
   inline constexpr pqs::basic_fixed_string fraction_slash<pqs::charset_utf8> = "\u002F";

   template <int N,typename CharSet >
   inline constexpr auto int_to_fixed_string()
   {
      if constexpr ( N < 0) 
         return minus_sign<CharSet> +
         int_to_fixed_string<-N,CharSet>();
      else if constexpr (N < 10)
         return exp_digit<N,CharSet>;
      else
         return int_to_fixed_string<N/10,CharSet>() + 
         int_to_fixed_string<N%10,CharSet>();
   }

   template <typename Exp,typename CharSet>
   inline constexpr pqs::basic_fixed_string fraction_to_fixed_string  =  
      int_to_fixed_string<Exp::num,CharSet>() +
      fraction_slash<CharSet> +
      int_to_fixed_string<Exp::den,CharSet>();
   ;

   template <>
   inline constexpr pqs::basic_fixed_string 
   fraction_to_fixed_string<std::ratio<1,2>,pqs::charset_utf8>
      = "\u00bd";

   template <>
   inline constexpr pqs::basic_fixed_string 
   fraction_to_fixed_string<std::ratio<1,3>,pqs::charset_utf8>
      = "\u2153";

   template <>
   inline constexpr pqs::basic_fixed_string 
   fraction_to_fixed_string<std::ratio<1,4>,pqs::charset_utf8>
      = "\u00bc";

   template <>
   inline constexpr pqs::basic_fixed_string 
   fraction_to_fixed_string<std::ratio<1,5>,pqs::charset_utf8>
      = "\u2155";

   template <>
   inline constexpr pqs::basic_fixed_string 
   fraction_to_fixed_string<std::ratio<2,3>,pqs::charset_utf8>
      = "\u2154";

   template <>
   inline constexpr pqs::basic_fixed_string 
   fraction_to_fixed_string<std::ratio<3,4>,pqs::charset_utf8>
      = "\u00be";

   template <typename Exp, typename CharSet>
   inline constexpr auto signed_fraction_to_fixed_string()
   {
      if constexpr ( Exp::num > 0)
         return fraction_to_fixed_string<Exp,CharSet>;
      else
         return minus_sign<CharSet> + 
         fraction_to_fixed_string<
            std::ratio_multiply<Exp,std::ratio<-1> > ,
            CharSet
         >;
   }

   template <typename Exp,typename CharSet>
   inline constexpr auto exponent_to_fixed_string()
   {
      if constexpr ( Exp::den == 1)
         return int_to_fixed_string<Exp::num,CharSet>();
      else 
         return signed_fraction_to_fixed_string<Exp,CharSet>();
   }

   template <pqs::base_quantity Qb, typename Exp, typename CharSet>
   inline constexpr auto get_base_unit_expression()
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
         return no_ext_str + exponent_to_fixed_string<Exp,CharSet>();      
   }
}

#if defined PQS_STANDALONE
int errors =0;
int main()
#else
void output_test()
#endif
{
   using base_quantity = pqs::base_mass;

   using exp = std::ratio<1,2>;
 #if 1
   using charset = pqs::charset_utf8;
 #else
   using charset = pqs::charset_ascii;
 #endif
   auto constexpr x = get_base_unit_expression<base_quantity,exp,charset>();

   std::cout << x <<'\n';
}
