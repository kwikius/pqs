
#include "test.hpp"

#include <pqs/bits/unit_to_fixed_string.hpp>
#include <pqs/si/units/area_unit.hpp>
#include <pqs/si/units/mass_unit.hpp>
#include <pqs/si/units/reciprocal_length_unit.hpp>
#include <pqs/si/units/reciprocal_mass_unit.hpp>
#include <pqs/si/units/reciprocal_mass2_unit.hpp>
#include <pqs/si/units/reciprocal_area_unit.hpp>

#include <pqs/si/time.hpp>
#include <pqs/si/speed.hpp>
#include <pqs/si/length.hpp>

#include <pqs/imperial/time.hpp>
#include <pqs/imperial/length.hpp>
#include <pqs/imperial/speed.hpp>
#include <pqs/bits/quantity_output.hpp>

#include <iostream>

using namespace pqs;

namespace {

   void unit_concept_test()
   {
      using U = si::normative_unit< 
         decltype( abstract_length<> * abstract_time<2> ),
         exponent10<1>
      >;

      static_assert( unit<U> );
      static_assert( si::is_normative_unit<U> );

      using D = get_dimension<U>;
      static_assert( dimension< D > );

      using Ds = get_simple_dimension< U > ;
      static_assert( dimension< Ds > );

      using Sm = get_measurement_system<U>;
      static_assert( measurement_system<Sm > );

      using Cf = get_conversion_factor< U >;
      static_assert( is_conversion_factor<Cf> );
   }

   void unit_binary_op_test()
   {
      pqs::basic_quantity<
         decltype( si::mass_unit::g() * si::area_unit::mm2() / si::time_unit::min()),
         double
      > q{123.45};

      output<charset_utf8>(std::cout,q) <<'\n';
   }

   void check_prefixable()
   {
      static_assert( pqs::si::is_prefixable<pqs::exp_time<1>,pqs::exponent10<0> >() );
      static_assert( not pqs::si::is_prefixable<pqs::exp_time<1>,pqs::exponent10<1,2> >() );
      static_assert( not pqs::si::is_prefixable<pqs::exp_time<1,2>,pqs::exponent10<0> >() );
      static_assert( pqs::si::is_prefixable<pqs::exp_time<3>,pqs::exponent10<0> >());
      static_assert( not pqs::si::is_prefixable<pqs::exp_time<3>,pqs::exponent10<2> >() );
      static_assert( not pqs::si::is_prefixable<
         decltype(pqs::abstract_time<3> * pqs::abstract_mass<2>) ,pqs::exponent10<0> >() );
      static_assert( pqs::si::is_prefixable<pqs::exp_mass<3>,pqs::exponent10<9> >() );

      static_assert( pqs::si::time_unit::ms::name<pqs::charset_utf8> == "ms");
    //  std::cout << "( should be ms )" << pqs::si::time_unit::ms::name<pqs::charset_utf8> <<'\n';
       static_assert(pqs::si::time_unit::s::name<pqs::charset_utf8> == "s");
     // std::cout << "( should be s )" << pqs::si::time_unit::s::name<pqs::charset_utf8> <<'\n';
      static_assert(pqs::si::area_unit::mm2::name<pqs::charset_utf8> == "mm²");
    //  std::cout << "( should be mm^2 )" << pqs::si::area_unit::mm2::name<pqs::charset_utf8> <<'\n';
      static_assert(pqs::si::area_unit::mm2::name<pqs::charset_ascii> == "mm2");
    //  std::cout << "( should be mm2 )" << pqs::si::area_unit::mm2::name<pqs::charset_ascii> <<'\n';
      static_assert(pqs::si::mass_unit::kg::name<pqs::charset_utf8> == "kg");
     // std::cout << "( should be kg )" << pqs::si::mass_unit::kg::name<pqs::charset_utf8> <<'\n';
      static_assert(pqs::si::mass_unit::kg::name<pqs::charset_ascii> == "kg");
     // std::cout << "( should be kg )" << pqs::si::mass_unit::kg::name<pqs::charset_ascii> <<'\n';

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
void unit_test()
#endif
{
   unit_concept_test();
   check_prefixable();
   unit_binary_op_test();
}
