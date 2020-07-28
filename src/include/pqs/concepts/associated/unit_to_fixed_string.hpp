#ifndef PQS_CONCEPTS_ASSOCIATED_UNIT_TO_FIXED_STRING_HPP_INCLUDED
#define PQS_CONCEPTS_ASSOCIATED_UNIT_TO_FIXED_STRING_HPP_INCLUDED

#include <pqs/concepts/associated/dimension_to_fixed_string.hpp>
#include <pqs/concepts/associated/unit_binary_op.hpp>

namespace pqs{

   template <unit U,typename CharSet>
   inline constexpr auto
   dimension_to_fixed_string()
   {
      return dimension_to_fixed_string<
         pqs::get_dimension<U>,
         pqs::get_measurement_system<U>,
         CharSet
      >();  
   }

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

}

#endif // PQS_CONCEPTS_ASSOCIATED_UNIT_TO_FIXED_STRING_HPP_INCLUDED
