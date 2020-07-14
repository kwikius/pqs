
#include <pqs/type_templates/conversion_factor.hpp>

#include <pqs/bits/unit_to_fixed_string.hpp>

#include <pqs/imperial/units/length_unit.hpp>
#include <pqs/imperial/units/speed_unit.hpp>

#include <pqs/si/units/area_unit.hpp>
#include <pqs/si/units/mass_unit.hpp>
#include <pqs/si/units/reciprocal_length_unit.hpp>
#include <pqs/si/units/reciprocal_mass_unit.hpp>
#include <pqs/si/units/reciprocal_mass2_unit.hpp>
#include <pqs/si/units/reciprocal_area_unit.hpp>
#include <pqs/imperial/time.hpp>
#include <pqs/imperial/length.hpp>
#include <pqs/imperial/speed.hpp>
#include <pqs/bits/base_quantities.hpp>
#include <pqs/si/time.hpp>
#include <pqs/si/speed.hpp>

#include <iostream>

namespace {

   void check_prefixable()
   {
      std::cout << "prefixable y = "  << pqs::si::is_prefixable<pqs::exp_time<1>,pqs::exponent10<0> >() <<'\n';
      std::cout << "prefixable n = "  << pqs::si::is_prefixable<pqs::exp_time<1>,pqs::exponent10<1,2> >() <<'\n';
      std::cout << "prefixable n = "  << pqs::si::is_prefixable<pqs::exp_time<1,2>,pqs::exponent10<0> >() <<'\n';
      std::cout << "prefixable y = "  << pqs::si::is_prefixable<pqs::exp_time<3>,pqs::exponent10<0> >() <<'\n';
      std::cout << "prefixable n = "  << pqs::si::is_prefixable<pqs::exp_time<3>,pqs::exponent10<2> >() <<'\n';
      std::cout << "prefixable n = "  << pqs::si::is_prefixable<
         decltype(pqs::abstract_time<3> * pqs::abstract_mass<2>) ,pqs::exponent10<0> >() <<'\n';
      std::cout << "prefixable y = "  << pqs::si::is_prefixable<pqs::exp_mass<3>,pqs::exponent10<6> >() <<'\n';

      std::cout << "( should be ms )" << pqs::si::time_unit::ms::name<pqs::charset_utf8> <<'\n';
      std::cout << "( should be s )" << pqs::si::time_unit::s::name<pqs::charset_utf8> <<'\n';
      std::cout << "( should be mm^2 )" << pqs::si::area_unit::mm2::name<pqs::charset_utf8> <<'\n';
      std::cout << "( should be mm2 )" << pqs::si::area_unit::mm2::name<pqs::charset_ascii> <<'\n';

      std::cout << "( should be kg )" << pqs::si::mass_unit::kg::name<pqs::charset_utf8> <<'\n';
      std::cout << "( should be kg )" << pqs::si::mass_unit::kg::name<pqs::charset_ascii> <<'\n';

      std::cout << "( should be g )" << pqs::si::mass_unit::g::name<pqs::charset_utf8> <<'\n';
      std::cout << "( should be g )" << pqs::si::mass_unit::g::name<pqs::charset_ascii> <<'\n';

      std::cout << "( should be m^-1 )" << pqs::si::reciprocal_length_unit::per_m::name<pqs::charset_utf8> <<'\n';
      std::cout << "( should be mm^-1 )" << pqs::si::reciprocal_length_unit::per_mm::name<pqs::charset_utf8> <<'\n';
      std::cout << "( should be km^-1 )" << pqs::si::reciprocal_length_unit::per_km::name<pqs::charset_utf8> <<'\n';

      std::cout << "( should be kg^-1 )" << pqs::si::reciprocal_mass_unit::per_kg::name<pqs::charset_utf8> <<'\n';
      std::cout << "( should be g^-1 )" << pqs::si::reciprocal_mass_unit::per_g::name<pqs::charset_utf8> <<'\n';
      std::cout << "( should be mg^-1 )" << pqs::si::reciprocal_mass_unit::per_mg::name<pqs::charset_utf8> <<'\n';
      std::cout << "( should be ug^-1 )" << pqs::si::reciprocal_mass_unit::per_ug::name<pqs::charset_utf8> <<'\n';

      std::cout << "( should be kg^-2 )" << pqs::si::reciprocal_mass2_unit::per_kg2::name<pqs::charset_utf8> <<'\n';
      std::cout << "( should be g^-2 )" << pqs::si::reciprocal_mass2_unit::per_g2::name<pqs::charset_utf8> <<'\n';
      std::cout << "( should be mg^-2 )" << pqs::si::reciprocal_mass2_unit::per_mg2::name<pqs::charset_utf8> <<'\n';
      std::cout << "( should be ug^-2 )" << pqs::si::reciprocal_mass2_unit::per_ug2::name<pqs::charset_utf8> <<'\n';

      std::cout << "( should be m^-2 )" << pqs::si::reciprocal_area_unit::per_m2::name<pqs::charset_utf8> <<'\n';
      std::cout << "( should be mm^-2 )" << pqs::si::reciprocal_area_unit::per_mm2::name<pqs::charset_utf8> <<'\n';
      std::cout << "( should be cm^-2 )" << pqs::si::reciprocal_area_unit::per_cm2::name<pqs::charset_utf8> <<'\n';
      std::cout << "( should be km^-2 )" << pqs::si::reciprocal_area_unit::per_km2::name<pqs::charset_utf8> <<'\n';
   }
}

#if defined PQS_STANDALONE
int errors =0;
int main()
#else
void sandbox()
#endif
{

   check_prefixable();
   namespace fps = pqs::imperial;
   
   auto q1 = fps::speed::mi_per_hr<>{10};
  
   using U1 = pqs::get_unit<decltype(q1)>;

   static_assert(pqs::is_unit_binary_op<U1>);

   std::cout << "q1 value = " << get_numeric_value(q1) << '\n';

   std::cout << "q1 dimension = " << 
      unit_to_fixed_string<pqs::charset_utf8>(q1) <<'\n';

   fps::speed::ft_per_s<> q2 = q1;

   std::cout << get_numeric_value(q2) <<'\n';

   fps::speed::mi_per_hr<> q3 = q2;

   std::cout << get_numeric_value(q3) << '\n';
//
   auto  str2 = pqs::unit_to_fixed_string<
      pqs::get_unit<decltype(q2)>,pqs::charset_utf8
   >();
   std::cout << "(should be ft/s) " << str2 <<'\n';

   auto  str1 = pqs::unit_to_fixed_string<
      pqs::charset_utf8
   >(q1);
   std::cout << "(should be mi/hr) " << str1 <<'\n';

   pqs::imperial::time::min<> q4{3};
   
   auto str4 =  pqs::unit_to_fixed_string<
      pqs::charset_utf8
   >(q4);

   std::cout << str4 <<'\n';

   fps::length::yd<> q5{1};

   using U5 = pqs::get_unit<decltype(q5)>;

   q1 = q5 / q4;

   std::cout << get_numeric_value(q1) << '\n';

   auto q6 = q5 * q4;

   auto str6 = pqs::unit_to_fixed_string<
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

   auto cf3 = std::ratio<7,3>() ^ pqs::exponent10<26,7>();

   std::cout << "cf3 =" << pqs::conversion_factor_to_fixed_string<
      decltype(cf3),
      pqs::charset_utf8
   >() << '\n';
   std::cout << "cf3 =" << pqs::conversion_factor_to_fixed_string<
      decltype(cf3),
      pqs::charset_ascii
   >() << '\n';
}
