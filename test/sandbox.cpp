
#include <pqs/imperial/units/length_unit.hpp>
#include <pqs/imperial/time.hpp>
#include <pqs/imperial/length.hpp>
#include <pqs/bits/dimension_as_fixed_string.hpp>

namespace pqs{

   namespace impl{
      // derive form here for type to be a basic_unit
      // and a unit_binary_op
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
   */
   template <unit UnitL, typename Op, unit UnitR>
      requires same_measurement_system<UnitL,UnitR>
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

      no_name_in_unit unit_has_name_test(...);

      template <unit T>
      auto unit_has_name_test(T) -> decltype(T::name);

      template <unit T>
      inline constexpr bool unit_has_name = 
         not std::is_same_v<
            decltype(unit_has_name_test(T())),
            no_name_in_unit
         >;
   }

   template <unit U,typename CharSet>
      requires detail::unit_has_name<U>
   inline constexpr 
   auto dimension_to_fixed_string()
   {
      return U::name;
   }

   template <unit U>
   inline constexpr bool is_unit_binary_op = 
      std::is_base_of_v<
         impl::unit_binary_op_base, 
         std::remove_cvref_t<U> 
      >;

   template <unit U,typename CharSet>
      requires is_unit_binary_op<U>
   inline constexpr 
   auto dimension_to_fixed_string()
   {
      return dimension_to_fixed_string<
         typename U::lhs_unit,CharSet
      >() +
       op_output_symbol<typename U::operation,CharSet> +
       dimension_to_fixed_string<
         typename U::rhs_unit,CharSet
      >(); 
   }

   template <typename CharSet, quantity Q>
      requires is_unit_binary_op<get_unit<Q> >
   inline constexpr auto
   dimension_to_fixed_string(Q)
   {
      return dimension_to_fixed_string<get_unit<Q>,CharSet>();
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
      return unit_binary_op<Lhs,divides,Rhs>{};
   }
}

#include <pqs/imperial/units/speed_unit.hpp>
#include <pqs/imperial/speed.hpp>
#include <pqs/si/time.hpp>

#include <iostream>

#if defined PQS_STANDALONE
int errors =0;
int main()
#else
void sandbox()
#endif
{
   namespace fps = pqs::imperial;
   
   auto constexpr q1 = fps::speed::mi_per_hr<>{10};
  
   using U1 = pqs::get_unit<decltype(q1)>;

   static_assert(pqs::is_unit_binary_op<U1>);

   std::cout << get_numeric_value(q1) << '\n';

   fps::speed::ft_per_s<> q2 = q1;

   std::cout << get_numeric_value(q2) <<'\n';

   fps::speed::mi_per_hr<> q3 = q2;

   std::cout << get_numeric_value(q3) << '\n';
//
   auto  str2 = pqs::dimension_to_fixed_string<
      pqs::get_unit<decltype(q2)>,pqs::charset_utf8
   >();
   std::cout << "(should be ft/s) " << str2 <<'\n';

   auto  str1 = pqs::dimension_to_fixed_string<
      pqs::charset_utf8
   >(q1);
   std::cout << "(should be mi/hr) " << str1 <<'\n';

   pqs::si::time::min<> q4{3};
   
   auto str4 =  pqs::dimension_to_fixed_string<
      pqs::charset_utf8
   >(q4);

   std::cout << str4 <<'\n';

   fps::length::yd<> q5{1};

   using U5 = pqs::get_unit<decltype(q5)>;

   //std::cout << pqs::get_unit<fps::length::yd<> >::name <<'\n';
   
}
