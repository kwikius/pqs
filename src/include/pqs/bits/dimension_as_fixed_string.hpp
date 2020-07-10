#ifndef PQS_OPERATIONS_DIMENSION_AS_FIXED_STRING_HPP_INCLUDED
#define PQS_OPERATIONS_DIMENSION_AS_FIXED_STRING_HPP_INCLUDED

#include <pqs/concepts/quantity.hpp>
#include <pqs/si/measurement_system.hpp>
#include <pqs/bits/fixed_string.hpp>
#include <pqs/bits/charset.hpp>

/**
 * @ brief encode a dimension to a fixed_string
 */

namespace pqs{

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

      // cant find a superscript fraction slash
      template<typename CharSet>
      inline constexpr 
      pqs::basic_fixed_string fraction_slash = '/';

      template <>
      inline constexpr 
      pqs::basic_fixed_string fraction_slash<
         pqs::charset_utf8
      > = "\u002F";

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
         fraction_slash<CharSet> +
         superscript_integer<Exp::den,CharSet>;
     
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

      template <typename Q,pqs::measurement_system Ms,typename CharSet>
      struct dimension_to_fixed_string_impl;
   }

   template < 
      pqs::dimension D, 
      pqs::measurement_system Ms, 
      typename CharSet
   >
   inline constexpr 
   auto dimension_to_fixed_string()
   {
      return detail::dimension_to_fixed_string_impl<
         std::remove_cvref_t<D>,Ms,CharSet
      >::apply();
   }

   template < 
      pqs::measurement_system Ms, 
      typename CharSet,
      pqs::dimension D
   >
   inline constexpr 
   auto dimension_to_fixed_string(D)
   {
      return detail::dimension_to_fixed_string_impl<
         std::remove_cvref_t<D>,Ms,CharSet
      >::apply();
   }

   namespace detail {

      // generic base_quantity_exponent output
      template <
         pqs::base_quantity_exponent Qbe,
         pqs::measurement_system Ms,
         typename CharSet
      >
      struct dimension_to_fixed_string_impl<
         Qbe,Ms,CharSet
      >{
         static constexpr auto apply()
         {
            using qB = pqs::get_base_quantity<Qbe>;
            using qE = pqs::get_exponent<Qbe>;

            auto constexpr no_ext_str = 
               pqs::get_base_unit_symbol<
                  qB,Ms,CharSet
               >;
            if constexpr ( std::ratio_equal_v<qE,std::ratio<1> > )
               return no_ext_str;
            else
               return no_ext_str + 
                  to_superscript_fixed_string<qE,CharSet>();      
         }
      };

      /**
       * @brief base_quantity exponent to fixed_string implementation
       * in SI. The kg has to be fixed up with a prefix
      */
      template <pqs::base_quantity_exponent Qbe,typename CharSet>
      struct dimension_to_fixed_string_impl<
         Qbe,pqs::si_measurement_system,CharSet
      >{
         static constexpr auto apply()
         {
            using qB = pqs::get_base_quantity<Qbe>;
            using qE = pqs::get_exponent<Qbe>;

            auto constexpr no_ext_str = 
               pqs::unit_symbol_prefix<
                 pqs::si::get_base_unit_prefix_offset<qB> 
                  ,CharSet
               > +
               pqs::get_base_unit_symbol<
                  qB,pqs::si_measurement_system,CharSet
               >;
            if constexpr ( std::ratio_equal_v<qE,std::ratio<1> > )
               return no_ext_str;
            else
               return no_ext_str + 
                  to_superscript_fixed_string<qE,CharSet>();      
         }
      };

      /**
       * @brief Single element dimension_list to fixed_string implementation
       * which terminates the dimensionlist dimension_to_fixed_string_impl recursion
      */
      template <pqs::base_quantity_exponent D,pqs::measurement_system Ms, typename CharSet>
      struct dimension_to_fixed_string_impl<
         pqs::dimension_list<D>,Ms,CharSet
      >{
         static constexpr auto apply()
         {   
            return dimension_to_fixed_string<
               D,pqs::si_measurement_system,CharSet
            >() ;   
         }
      };

      /**
       * @brief Multi element dimension_list to fixed_string implementation
       * https://www.nist.gov/pml/special-publication-811/nist-guide-si-chapter-6-rules-and-style-conventions-printing-and-using
      */
      template <
         pqs::base_quantity_exponent... D,
         pqs::measurement_system Ms, 
         typename CharSet
      >
      struct dimension_to_fixed_string_impl<
         pqs::dimension_list<D...>,Ms, CharSet
      >{
         static constexpr auto apply()
         {   
            using list = pqs::dimension_list<D...>;
            return dimension_to_fixed_string<
               pqs::meta::front_t<list>,
               Ms,
               CharSet
            >() + 
            multiplication_dot<CharSet> +
            dimension_to_fixed_string<
               pqs::meta::pop_front_t<list>,
               Ms, 
               CharSet
            >(); 
         }
      };

      /**
       * @brief Custom dimension to fixed_string implementation
      */
      template <typename D,pqs::measurement_system Ms,typename CharSet>
         requires pqs::is_custom_dimension<D>
      struct dimension_to_fixed_string_impl<
         D,Ms, CharSet
      >{
         static constexpr auto apply()
         {   
            return dimension_to_fixed_string<
               pqs::get_simple_dimension<D>,
               Ms,
               CharSet
            >();   
         }
      };

   }// detail

   template <quantity Q,typename CharSet>
   inline constexpr auto
   dimension_to_fixed_string()
   {
      return dimension_to_fixed_string<
         pqs::get_dimension<Q>,
         pqs::get_measurement_system<Q>,
         CharSet
      >();  
   }

   template <typename CharSet, quantity Q>
   inline constexpr auto
   dimension_to_fixed_string(Q)
   {
      return dimension_to_fixed_string<
         pqs::get_dimension<Q>,
         pqs::get_measurement_system<Q>,
         CharSet
      >();  
   }

} // pqs

#endif // PQS_OPERATIONS_DIMENSION_AS_FIXED_STRING_HPP_INCLUDED
