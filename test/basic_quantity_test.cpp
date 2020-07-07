#include "test.hpp"
#include <pqs/bits/base_quantities.hpp>
#include <pqs/instance/basic_quantity.hpp>
#include <pqs/bits/basic_unit.hpp>
#include <pqs/si/length.hpp>
#include <pqs/imperial/length.hpp>
#include <iostream>

struct dummy_system{ 

   typedef dummy_system type; 
};

namespace pqs{
   namespace impl{
      template <> struct is_measurement_system_impl<::dummy_system> : std::true_type{};
   }
}

namespace {

   void basic_quantity_test1()
   {
      static_assert(pqs::is_defined_legacy<double>::value,"");
      pqs::basic_quantity<
         pqs::basic_unit<
            dummy_system,
            decltype(pqs::abstract_length<> / pqs::abstract_time<> ),
            decltype( std::ratio<30,2>{} * pqs::exponent10<3>{})
         >, double
      > constexpr q{20.0};

      using tu = pqs::get_unit<decltype(q)>;
         
      using td = pqs::get_dimension<decltype(q)>;

      using tv = pqs::get_numeric_type<decltype(q)>;

      using tcf = pqs::get_conversion_factor<decltype(q)>;

      using ts = pqs::get_measurement_system<decltype(q)>;

      auto constexpr v = get_numeric_value(q);
     
      std::cout << " qs numeric value = " << v << '\n';

      QUAN_CHECK(( v == 20.0 ))

      auto constexpr r = q + q;

      QUAN_CHECK(( get_numeric_value(r) == 40.0))

     // int x = r;
   }

   void basic_quantity_test2()
   {
      auto q_si1 = pqs::si::length::m<>{1};
      auto q_si2 = pqs::si::length::mm<>{321};
      auto q_sir = q_si1 + q_si2;
      QUAN_CHECK( (get_numeric_value(q_sir) == 1321))
      std::cout << " q_r numeric value = " << get_numeric_value(q_sir) << '\n';

      auto q_si3 = pqs::si::length::ft<>{6};
      auto q_sir1 = q_si1 + q_si3;
      std::cout << " q_r numeric value = " << get_numeric_value(q_sir1) << '\n';
      QUAN_CHECK(( std::is_same_v<
         pqs::get_conversion_factor<decltype(q_sir1)>,
         pqs::conversion_factor<std::ratio<1>,pqs::exponent10<-1> >
      > ))

      auto b = pqs::imperial::length::ft<>{1};
      auto c = pqs::imperial::length::yd<>{2};
      auto d = b + c;
      QUAN_CHECK( (get_numeric_value(d) == 7))
      std::cout << " imp numeric value = " << get_numeric_value(d) << '\n';
   }
}

void basic_quantity_test()
{
   basic_quantity_test1();
   basic_quantity_test2();
}