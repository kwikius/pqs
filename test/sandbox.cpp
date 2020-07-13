
#include <pqs/imperial/units/length_unit.hpp>
#include <pqs/imperial/time.hpp>
#include <pqs/imperial/length.hpp>
#include <pqs/si/speed.hpp>
#include <pqs/bits/dimension_to_fixed_string.hpp>
#include <pqs/type_templates/conversion_factor.hpp>
#include <pqs/bits/conversion_factor_to_fixed_string.hpp>

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

   template <unit U, typename CharSet>
   inline constexpr
   auto unit_to_fixed_string()
   {
      
   }

   template <unit U,typename CharSet>
      requires detail::unit_has_name<U,CharSet>
   inline constexpr 
   auto dimension_to_fixed_string()
   {
      return U::template name<CharSet>;
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
   inline constexpr 
   auto dimension_to_fixed_string(Q)
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
      return unit_binary_op<Lhs,times,Rhs>{};
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
   
   auto q1 = fps::speed::mi_per_hr<>{10};
  
   using U1 = pqs::get_unit<decltype(q1)>;

   static_assert(pqs::is_unit_binary_op<U1>);

   std::cout << "q1 value = " << get_numeric_value(q1) << '\n';

   std::cout << "q1 dimension = " << 
      dimension_to_fixed_string<pqs::charset_utf8>(q1) <<'\n';

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

   pqs::imperial::time::min<> q4{3};
   
   auto str4 =  pqs::dimension_to_fixed_string<
      pqs::charset_utf8
   >(q4);

   std::cout << str4 <<'\n';

   fps::length::yd<> q5{1};

   using U5 = pqs::get_unit<decltype(q5)>;

   q1 = q5 / q4;

   std::cout << get_numeric_value(q1) << '\n';

   auto q6 = q5 * q4;

   auto str6 = pqs::dimension_to_fixed_string<
      pqs::charset_utf8
   >(q6);
   std::cout << "str6 = " <<  str6 << '\n';
   std::cout << " yd has name = " << pqs::detail::unit_has_name<pqs::get_unit<fps::length::yd<> >,pqs::charset_ascii > << '\n';
   std::cout << " ft has name = " << pqs::detail::unit_has_name<pqs::get_unit<fps::length::ft<> >,pqs::charset_ascii > << '\n';
   std::cout << pqs::get_unit<fps::length::ft<> >::name<pqs::charset_utf8> <<'\n';
   std::cout << pqs::get_unit<fps::length::ft<> >::name<pqs::charset_ascii> <<'\n';
   std::cout << pqs::get_unit<fps::length::yd<> >::name<pqs::charset_utf8> <<'\n';
   std::cout << pqs::get_unit<fps::length::yd<> >::name<pqs::charset_ascii> <<'\n';
  

   using q_type = pqs::imperial::length::mi<> ;
   std::cout <<"q_type cf = " << pqs::conversion_factor_to_fixed_string<
      pqs::get_conversion_factor<q_type>,
      pqs::charset_utf8
   >() <<'\n';

   std::cout <<"q_type cf = " << pqs::conversion_factor_to_fixed_string<
      pqs::get_conversion_factor<q_type>,
      pqs::charset_ascii
   >() <<'\n';
;

   std::cout << "eval q_type = " << pqs::evaluate<pqs::get_conversion_factor<q_type> >() <<'\n';

   using q_type1 = pqs::imperial::length::ft<> ;
   std::cout <<"q_type1 cf = " << pqs::conversion_factor_to_fixed_string<
      pqs::get_conversion_factor<q_type1>,
      pqs::charset_utf8
   >() <<'\n';

   std::cout <<"q_type1 cf = " << pqs::conversion_factor_to_fixed_string<
      pqs::get_conversion_factor<q_type1>,
      pqs::charset_ascii
   >() <<'\n';
   std::cout << "eval q_type1 cf = " << static_cast<double>(pqs::evaluate<pqs::get_conversion_factor<q_type1> >()) <<'\n';

   auto cf3 = std::ratio<7,3>() ^ pqs::exponent10<26>();

   std::cout << "cf3 =" << pqs::conversion_factor_to_fixed_string<
      decltype(cf3),
      pqs::charset_utf8
   >() << '\n';
   std::cout << "cf3 =" << pqs::conversion_factor_to_fixed_string<
      decltype(cf3),
      pqs::charset_ascii
   >() << '\n';

}

#if 0
      /**
       * @brief SI specific base_quantity exponent
       * to fixed_string.
       * The kg has to be fixed up with a prefix
       */
      template <
         pqs::base_quantity_exponent Qbe,
         typename CharSet
      >
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
               // get_unprefixed_base_unit_symbol
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
#endif

