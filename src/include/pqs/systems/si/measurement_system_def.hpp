#ifndef PQS_BITS_SI_QUANTITY_SYSTEM_DEF_HPP_INCLUDED
#define PQS_BITS_SI_QUANTITY_SYSTEM_DEF_HPP_INCLUDED

#include <pqs/concepts/measurement_system.hpp>
#include <pqs/concepts/associated/get_base_unit_symbol.hpp>
#include <pqs/concepts/quantity.hpp>
#include <pqs/systems/si/get_base_unit_prefix_offset.hpp>
#include <pqs/types/base_quantities.hpp>
#include <pqs/types/fixed_string.hpp>
#include <pqs/types/conversion_factor.hpp>

namespace pqs{ 

   struct  si_measurement_system {
      using type = si_measurement_system;
   };

} //pqs

namespace pqs{

   namespace impl{
      template <> struct is_measurement_system_impl<
         pqs::si_measurement_system
      > : std::true_type{};
   }
}

namespace pqs{

   namespace si{

      template <>
      inline constexpr int get_base_unit_prefix_offset<base_mass> = 3;

      template <quantity Lhs, quantity Rhs>
      inline constexpr bool are_in_si_measurement_system
         = std::is_same_v<get_measurement_system<Lhs>,si_measurement_system> &&
         std::is_same_v<get_measurement_system<Rhs>,si_measurement_system>
      ;

      template <base_quantity Q, typename CharSet>
      inline constexpr 
      basic_fixed_string get_unprefixed_base_unit_symbol = 
         pqs::get_base_unit_symbol<Q,si_measurement_system,CharSet>;

      template <typename CharSet>
      inline constexpr 
      basic_fixed_string get_unprefixed_base_unit_symbol<
         pqs::base_mass ,CharSet
      > = "g";
   }

   template <typename Charset>
   inline constexpr pqs::basic_fixed_string
   get_base_unit_symbol<
      base_length,si_measurement_system,Charset
   > = "m";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string
   get_base_unit_symbol<
      base_mass,si_measurement_system,CharSet
   > = "kg";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string
   get_base_unit_symbol<
      base_time,si_measurement_system,CharSet
   > = "s";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string
   get_base_unit_symbol<
      base_current,si_measurement_system,CharSet
   > = "A";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string
   get_base_unit_symbol<
      base_temperature,si_measurement_system,CharSet
   > = "K";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string
   get_base_unit_symbol<
      base_substance,si_measurement_system,CharSet
   > = "mol";

   template <typename CharSet>
   inline constexpr pqs::basic_fixed_string
   get_base_unit_symbol<
      base_intensity,si_measurement_system,CharSet
   > = "cd";

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

#endif // PQS_BITS_SI_QUANTITY_SYSTEM_DEF_HPP_INCLUDED
