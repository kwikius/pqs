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
        auto a = pqs::si::length::ft<>{1};

        auto b = pqs::imperial::length::ft<>{1};

        auto c1 = a + a;
       // auto c2 = b + b;
       // auto c3 = a + b;
   }

}



void basic_quantity_test()
{
   basic_quantity_test1();
   basic_quantity_test2();
}