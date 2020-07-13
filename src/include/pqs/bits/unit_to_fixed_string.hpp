#ifndef PQS_BITS_UNIT_TO_FIXED_STRING_HPP_INCLUDED
#define PQS_BITS_UNIT_TO_FIXED_STRING_HPP_INCLUDED


#include <pqs/type_templates/conversion_factor.hpp>
#include <pqs/bits/dimension_to_fixed_string.hpp>

namespace pqs{

   namespace impl{
      struct unit_binary_op_base : basic_unit_base{};
   }

   template <typename Op, typename CharSet>
   inline constexpr auto op_output_symbol = pqs::undefined_arg<Op,CharSet>();

   template <typename CharSet>
   inline constexpr auto op_output_symbol<times, CharSet>
     = detail::multiplication_dot<CharSet>;

   template <typename CharSet>
   inline constexpr auto op_output_symbol<divides, CharSet>
     = detail::fraction_slash<CharSet>;

   /*
      creates a model of unit fromed from binary op on 
      two units
      call it a composition op
   */
   template <unit UnitL, typename Op, unit UnitR>
      requires same_measurement_system<UnitL,UnitR>
            && meta::is_multiplicative_operator<Op>::value
   struct unit_binary_op : impl::unit_binary_op_base{

      using type = unit_binary_op;
      using lhs_unit = UnitL;
      using operation = Op;
      using rhs_unit = UnitR;

      using quantity_system = 
         get_measurement_system<lhs_unit>;

      using dimension = 
         binary_op_t<
            get_dimension<lhs_unit>,
            Op,
            get_dimension<rhs_unit>
         >;
      using conversion_factor = 
         binary_op_t<
            get_conversion_factor<lhs_unit>,
            Op,
            get_conversion_factor<rhs_unit>
         >;       
   };

   namespace detail{

      struct no_name_in_unit{};

      template <typename CharSet>
      no_name_in_unit unit_has_name_test(...);

      template <typename CharSet, unit T>
      auto unit_has_name_test(T) -> decltype(T::template name<CharSet>);

      template <unit T, typename CharSet>
      inline constexpr bool unit_has_name = 
         not std::is_same_v<
            decltype(unit_has_name_test<CharSet>(T())),
            no_name_in_unit
         >;
   }

   template <unit U>
   inline constexpr bool is_unit_binary_op = 
      std::is_base_of_v<
         impl::unit_binary_op_base, 
         std::remove_cvref_t<U> 
      >;

   // default unnamed unit
   template <unit U, typename CharSet>
   inline constexpr
   auto unit_to_fixed_string()
   {
      using cf = get_conversion_factor<U>;
      if constexpr (pqs::evaluate<cf>() == 1)
         return dimension_to_fixed_string<U,CharSet>();
      else 
         return dimension_to_fixed_string<U,CharSet>() +
         detail::multiplication_dot<CharSet> +
         conversion_factor_to_fixed_string<get_conversion_factor<U>,CharSet>();
   }

   // named unit
   template <unit U,typename CharSet>
      requires detail::unit_has_name<U,CharSet>
   inline constexpr 
   auto unit_to_fixed_string()
   {
      return U::template name<CharSet>;
   }

   // unit binary expression
   template <unit U,typename CharSet>
      requires is_unit_binary_op<U>
   inline constexpr 
   auto unit_to_fixed_string()
   {
      return unit_to_fixed_string<
         typename U::lhs_unit,CharSet
      >() +
       op_output_symbol<typename U::operation,CharSet> +
       unit_to_fixed_string<
         typename U::rhs_unit,CharSet
      >(); 
   }

   template <typename CharSet, quantity Q>
     // requires is_unit_binary_op<get_unit<Q> >
   inline constexpr 
   auto unit_to_fixed_string(Q)
   {
      return unit_to_fixed_string<get_unit<Q>,CharSet>();
   }

   template <unit Lhs, unit Rhs>
   inline constexpr
   auto operator/( Lhs, Rhs)
   {
      return unit_binary_op<Lhs,divides,Rhs>{};
   }

   template <unit Lhs, unit Rhs>
   inline constexpr
   auto operator*( Lhs, Rhs)
   {
      return unit_binary_op<Lhs,times,Rhs>{};
   }
}

#endif // PQS_BITS_UNIT_TO_FIXED_STRING_HPP_INCLUDED
