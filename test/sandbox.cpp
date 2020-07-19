

#include "test.hpp"
#include <iostream>
#include <pqs/systems/imperial/speed.hpp>
#include <pqs/systems/imperial/time.hpp>
#include <pqs/systems/imperial/length.hpp>
#include <pqs/concepts/associated/quantity_to_fixed_string.hpp>

namespace {
   void bits_function();
}

#if defined PQS_STANDALONE
int errors =0;
int main()
#else
void sandbox()
#endif
{
  bits_function();
}

namespace {

   void bits_function()
   {
     // check_prefixable();
      namespace fps = pqs::imperial;
      
      auto q1 = fps::speed::mi_per_hr<>{10};
     
      using U1 = pqs::get_unit<decltype(q1)>;

      static_assert(pqs::is_unit_binary_op<U1>);

     // std::cout << "q1 value = " << get_numeric_value(q1) << '\n';

     // std::cout << "q1 dimension = " << 
   //      unit_to_fixed_string<pqs::charset_utf8>(q1) <<'\n';

      fps::speed::ft_per_s<> q2 = q1;

     // std::cout << get_numeric_value(q2) <<'\n';

      fps::speed::mi_per_hr<> q3 = q2;

     // std::cout << get_numeric_value(q3) << '\n';
   //
      auto  str2 = pqs::unit_to_fixed_string<
         pqs::get_unit<decltype(q2)>,pqs::charset_utf8
      >();
    //  std::cout << "(should be ft/s) " << str2 <<'\n';

      auto  str1 = pqs::unit_to_fixed_string<
         pqs::charset_utf8
      >(q1);
     // std::cout << "(should be mi/hr) " << str1 <<'\n';

      pqs::imperial::time::min<> q4{3};
      
      auto str4 =  pqs::unit_to_fixed_string<
         pqs::charset_utf8
      >(q4);

     // std::cout << str4 <<'\n';

      fps::length::yd<> q5{1};

      using U5 = pqs::get_unit<decltype(q5)>;

      q1 = q5 / q4;

     // std::cout << get_numeric_value(q1) << '\n';

      auto q6 = q5 * q4;

      auto str6 = pqs::unit_to_fixed_string<
         pqs::charset_utf8
      >(q6);
   //   std::cout << "str6 = " <<  str6 << '\n';
   //   std::cout << " yd has name = " << pqs::detail::unit_has_name<pqs::get_unit<fps::length::yd<> >,pqs::charset_ascii > << '\n';
   //   std::cout << " ft has name = " << pqs::detail::unit_has_name<pqs::get_unit<fps::length::ft<> >,pqs::charset_ascii > << '\n';
   //   std::cout << pqs::get_unit<fps::length::ft<> >::name<pqs::charset_utf8> <<'\n';
   //   std::cout << pqs::get_unit<fps::length::ft<> >::name<pqs::charset_ascii> <<'\n';
   //   std::cout << pqs::get_unit<fps::length::yd<> >::name<pqs::charset_utf8> <<'\n';
   //   std::cout << pqs::get_unit<fps::length::yd<> >::name<pqs::charset_ascii> <<'\n';
     

      using q_type = pqs::imperial::length::mi<> ;
   //   std::cout <<"q_type cf = " << pqs::conversion_factor_to_fixed_string<
   //      pqs::get_conversion_factor<q_type>,
   //      pqs::charset_utf8
   //   >() <<'\n';

   //   std::cout <<"q_type cf = " << pqs::conversion_factor_to_fixed_string<
   //      pqs::get_conversion_factor<q_type>,
   //      pqs::charset_ascii
   //   >() <<'\n';
   //;
   //
   //   std::cout << "eval q_type = " << pqs::evaluate<pqs::get_conversion_factor<q_type> >() <<'\n';

      using q_type1 = pqs::imperial::length::ft<> ;
   //   std::cout <<"q_type1 cf = " << pqs::conversion_factor_to_fixed_string<
   //      pqs::get_conversion_factor<q_type1>,
   //      pqs::charset_utf8
   //   >() <<'\n';

   //   std::cout <<"q_type1 cf = " << pqs::conversion_factor_to_fixed_string<
   //      pqs::get_conversion_factor<q_type1>,
   //      pqs::charset_ascii
   //   >() <<'\n';
   //   std::cout << "eval q_type1 cf = " << static_cast<double>(pqs::evaluate<pqs::get_conversion_factor<q_type1> >()) <<'\n';

      auto cf3 = std::ratio<7,3>() ^ pqs::exponent10<26,7>();

   //   std::cout << "cf3 =" << pqs::conversion_factor_to_fixed_string<
   //      decltype(cf3),
   //      pqs::charset_utf8
   //   >() << '\n';
   //   std::cout << "cf3 =" << pqs::conversion_factor_to_fixed_string<
   //      decltype(cf3),
   //      pqs::charset_ascii
   //   >() << '\n';
   }


}