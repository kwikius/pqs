
#include "test.hpp"
#include <pqs/concepts/dimension.hpp>
#include <pqs/si/measurement_system.hpp>
#include <pqs/bits/abs.hpp>
#include <string>

/**
 * @ brief output a base_dimension_exponent.
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
   inline constexpr pqs::basic_fixed_string minus_sign = '-';

   template <>
   inline constexpr pqs::basic_fixed_string minus_sign<pqs::charset_utf8> = "\u207b";

   template<typename CharSet>
   inline constexpr pqs::basic_fixed_string fraction_slash = '/';
   
   template <>
   inline constexpr pqs::basic_fixed_string fraction_slash<pqs::charset_utf8> = "\u002F";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string multiplication_dot = '.';

   template <>
   inline constexpr pqs::basic_fixed_string multiplication_dot<pqs::charset_utf8> = "\u22C5";

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
        // int_to_fixed_string<N%10,CharSet>();
         exp_digit<N%10,CharSet>;
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
        requires pqs::is_ratio<Exp>
   inline constexpr auto to_superscript_fixed_string()
   {
      if constexpr ( Exp::den == 1)
         return int_to_fixed_string<Exp::num,CharSet>();
      else 
         return signed_fraction_to_fixed_string<Exp,CharSet>();
   }

   template <typename CharSet, typename Q>
   struct to_fixed_string_impl;

// ######## n.b specific to S.I. ####################
   template <typename CharSet,pqs::base_quantity_exponent Qbe>
   struct to_fixed_string_impl<CharSet,Qbe>{
      static constexpr auto apply()
      {
         using Qb = pqs::get_base_quantity<Qbe>;
         using Exp = pqs::get_exponent<Qbe>;

         auto constexpr no_ext_str = 
            pqs::unit_symbol_prefix<
              pqs::si::get_base_unit_prefix_offset<Qb> 
               ,CharSet
            > +
            pqs::get_base_unit_symbol<
               Qb,pqs::si_measurement_system,CharSet
            >;
         if constexpr ( std::ratio_equal_v<Exp,std::ratio<1> > )
            return no_ext_str;
         else
            return no_ext_str + to_superscript_fixed_string<Exp,CharSet>();      
      }
   };

   template <typename CharSet, typename Q>
   inline constexpr auto to_fixed_string()  
   {
      return to_fixed_string_impl<CharSet,std::remove_cvref_t<Q> >::apply();
   }

   template <typename CharSet,pqs::base_quantity_exponent D>
   struct to_fixed_string_impl<CharSet,pqs::dimension_list<D> >{
      
      static constexpr auto apply()
      {   
         using list = pqs::dimension_list<D>;
         return to_fixed_string<
             CharSet,
             typename pqs::meta::front<list>::type
         >() ;   
      }
   };

   template <typename CharSet,pqs::base_quantity_exponent... D>
   struct to_fixed_string_impl<CharSet,pqs::dimension_list<D...> >{
      
      static constexpr auto apply()
      {   
         using list = pqs::dimension_list<D...>;
         return to_fixed_string<
            CharSet,
            typename pqs::meta::front<list>::type
         >() + 
         multiplication_dot<CharSet>
         + to_fixed_string<CharSet, typename pqs::meta::pop_front<list>::type>(); 
      }
   };

}

//https://www.nist.gov/pml/special-publication-811/nist-guide-si-chapter-6-rules-and-style-conventions-printing-and-using

#if defined PQS_STANDALONE
int errors = 0;
int main()
#else
void output_test()
#endif
{
   using Qbe = pqs::exp_mass<-1,2>;
 #if 0
   using charset = pqs::charset_utf8;
 #else
   using charset = pqs::charset_ascii;
 #endif
   auto constexpr x = to_fixed_string<charset,Qbe>();

   std::cout << x <<'\n';

   using D = decltype(pqs::abstract_time<3> * pqs::abstract_length<-3> * pqs::abstract_current<-1>);
   std::cout << to_fixed_string<charset,D>() << '\n';
}
