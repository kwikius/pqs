#ifndef PQS_SYSTEMS_SI_QUANTITY_UNIT_SYMBOL_PREFIX_HPP_INCLUDED
#define PQS_SYSTEMS_SI_QUANTITY_UNIT_SYMBOL_PREFIX_HPP_INCLUDED

#include <pqs/types/fixed_string.hpp>

namespace pqs::si{

   template <int Exp10, typename CharSet>
   inline constexpr pqs::basic_fixed_string unit_symbol_prefix = "";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string unit_symbol_prefix<-24, CharSet> = "y";
   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string unit_symbol_prefix<-21, CharSet> = "z";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string unit_symbol_prefix<-18, CharSet> = "a";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string unit_symbol_prefix<-15, CharSet> = "f";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string unit_symbol_prefix<-12, CharSet> = "p";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string unit_symbol_prefix<-9, CharSet> = "n";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string unit_symbol_prefix<-6, CharSet> = "u";

   template <>
   inline constexpr pqs::basic_fixed_string unit_symbol_prefix<-6, charset_utf8> = "\u00B5";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string unit_symbol_prefix<-3, CharSet> = "m";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string unit_symbol_prefix<-2, CharSet> = "c";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string unit_symbol_prefix<-1, CharSet> = "d";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string unit_symbol_prefix<0, CharSet> = "";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string unit_symbol_prefix<1, CharSet> = "da";
   
   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string unit_symbol_prefix<2, CharSet> = "h";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string unit_symbol_prefix<3, CharSet> = "k";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string unit_symbol_prefix<6, CharSet> = "M";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string unit_symbol_prefix<9, CharSet> = "G";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string unit_symbol_prefix<12, CharSet> = "T";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string unit_symbol_prefix<15, CharSet> = "P";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string unit_symbol_prefix<18, CharSet> = "E";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string unit_symbol_prefix<21, CharSet> = "Z";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string unit_symbol_prefix<24, CharSet> = "Y";

}

#endif // PQS_SYSTEMS_SI_QUANTITY_UNIT_SYMBOL_PREFIX_HPP_INCLUDED
