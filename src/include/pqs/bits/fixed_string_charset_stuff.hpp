#ifndef PQS_BITS_FIXED_STRING_STUFF_HPP_INCLUDED
#define PQS_BITS_FIXED_STRING_STUFF_HPP_INCLUDED

#include <pqs/bits/undefined_arg.hpp>
#include <pqs/types/charset.hpp>
#include <pqs/types/fixed_string.hpp>

// Copyright (c) Andy Little 2020

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

namespace pqs{

  /*
      TODO superscript ascii number is same as regular_ascii number
   */

   namespace detail {

     /**
      * @brief default digit output to ascii
      */
      template<int N, typename CharSet>
         requires (N >=0 ) && (N < 10)
      inline constexpr 
      pqs::basic_fixed_string superscript_digit = 
         static_cast<char>( N + '0');

      /**
      * @brief specialise digit output for unocode
      */
      template<> inline constexpr 
      pqs::basic_fixed_string superscript_digit<
         0,pqs::charset_utf8
      > = "\u2070";

      template<> inline constexpr 
      pqs::basic_fixed_string superscript_digit<
         1,pqs::charset_utf8
      > = "\u00b9";

      template<> inline constexpr 
      pqs::basic_fixed_string superscript_digit<
         2,pqs::charset_utf8
      > = "\u00b2";

      template<> inline constexpr 
      pqs::basic_fixed_string superscript_digit<
         3,pqs::charset_utf8
      > = "\u00b3";

      template<> inline constexpr 
      pqs::basic_fixed_string superscript_digit<
         4,pqs::charset_utf8
      > = "\u2074";

      template<> inline constexpr 
      pqs::basic_fixed_string superscript_digit<
         5,pqs::charset_utf8
      > = "\u2075";

      template<> inline constexpr 
      pqs::basic_fixed_string superscript_digit<
         6,pqs::charset_utf8
      > = "\u2076";

      template<> inline constexpr 
      pqs::basic_fixed_string superscript_digit<
         7,pqs::charset_utf8
      > = "\u2077";

      template<> inline constexpr 
      pqs::basic_fixed_string superscript_digit<
         8,pqs::charset_utf8
      > = "\u2078";

      template<> inline constexpr 
      pqs::basic_fixed_string superscript_digit<
         9,pqs::charset_utf8
      > = "\u2079";

      template<typename CharSet>
      inline constexpr 
      pqs::basic_fixed_string superscript_minus = '-';

      template <>
      inline constexpr 
      pqs::basic_fixed_string superscript_minus<
         pqs::charset_utf8
      > = "\u207b";


      template<typename CharSet>
      inline constexpr 
      pqs::basic_fixed_string superscript_fraction_slash = '/';

      template<>
      inline constexpr 
      pqs::basic_fixed_string superscript_fraction_slash<charset_utf8> = "\u2044";

      template<typename CharSet>
      inline constexpr 
      pqs::basic_fixed_string fraction_slash = '/';

      template <>
      inline constexpr 
      pqs::basic_fixed_string fraction_slash<
         pqs::charset_utf8
      > = "\u2044"; //2019

      template <typename CharSet>
      inline constexpr 
      pqs::basic_fixed_string multiplication_dot = '.';

      template <>
      inline constexpr 
      pqs::basic_fixed_string multiplication_dot<
         pqs::charset_utf8
      > = "\u22C5";

      template <int N,typename CharSet >
      inline constexpr auto superscript_integer_impl()
      {
         if constexpr ( N < 0) 
            return superscript_minus<CharSet> +
            superscript_integer_impl<-N,CharSet>();
         else if constexpr (N < 10)
            return superscript_digit<N,CharSet>;
         else
            return superscript_integer_impl<N/10,CharSet>() + 
            superscript_digit<N%10,CharSet>;
      }

      template <int N,typename CharSet >
      inline constexpr
      pqs::basic_fixed_string superscript_integer =
         detail::superscript_integer_impl<N,CharSet>();

      template <typename Exp,typename CharSet>
      inline constexpr pqs::basic_fixed_string 
      superscript_fraction =  
         superscript_integer<Exp::num,CharSet> +
         superscript_fraction_slash<CharSet> +
         superscript_integer<Exp::den,charset_ascii>;
     
      template <>
      inline constexpr pqs::basic_fixed_string 
      superscript_fraction<
         std::ratio<1,2>,pqs::charset_utf8
      > = "\u00bd";

      template <>
      inline constexpr pqs::basic_fixed_string 
      superscript_fraction<
         std::ratio<1,3>,pqs::charset_utf8
      > = "\u2153";

      template <>
      inline constexpr pqs::basic_fixed_string 
      superscript_fraction<
         std::ratio<1,4>,pqs::charset_utf8
      > = "\u00bc";

      template <>
      inline constexpr pqs::basic_fixed_string 
      superscript_fraction<
         std::ratio<1,5>,pqs::charset_utf8
      > = "\u2155";

      template <>
      inline constexpr pqs::basic_fixed_string 
      superscript_fraction<
         std::ratio<2,3>,pqs::charset_utf8
      > = "\u2154";

      template <>
      inline constexpr pqs::basic_fixed_string 
      superscript_fraction<
         std::ratio<3,4>,pqs::charset_utf8
      > = "\u00be";

      template <typename Exp, typename CharSet>
      inline constexpr auto signed_superscript_fraction()
      {
         if constexpr ( Exp::num > 0)
            return superscript_fraction<Exp,CharSet>;
         else
            return superscript_minus<CharSet> + 
            superscript_fraction<
               std::ratio_multiply<Exp,std::ratio<-1> > ,
               CharSet
            >;
      }

      template <typename Exp,typename CharSet>
           requires pqs::is_ratio<Exp>
      inline constexpr auto to_superscript_fixed_string()
      {
         if constexpr ( Exp::den == 1)
            return superscript_integer<Exp::num,CharSet>;
         else 
            return signed_superscript_fraction<Exp,CharSet>();
      }

      template <typename Exp,typename CharSet>
           requires pqs::is_ratio<Exp>
      inline constexpr auto to_regular_fixed_string()
      {
         if constexpr ( Exp::den == 1)
            return superscript_integer<Exp::num,charset_ascii>;
         else 
            return signed_superscript_fraction<Exp,charset_ascii>();
      }
   }// detail

   template <typename Op, typename CharSet>
   inline constexpr auto op_output_symbol = pqs::undefined_arg<Op,CharSet>();

   template <typename CharSet>
   inline constexpr auto op_output_symbol<times, CharSet>
     = detail::multiplication_dot<CharSet>;

   template <typename CharSet>
   inline constexpr auto op_output_symbol<divides, CharSet>
     = detail::fraction_slash<CharSet>;

}// pqs



#endif // PQS_BITS_FIXED_STRING_STUFF_HPP_INCLUDED
