

#include <pqs/bits/base_quantities.hpp>

#include <pqs/instance/basic_quantity.hpp>
#include <pqs/bits/basic_unit.hpp>

#include <iostream>

struct dummy_system{ typedef dummy_system type; };

void basic_quantity_test()
{
   pqs::basic_quantity<
      pqs::basic_unit<
         dummy_system,
         decltype(pqs::abstract_length<> / pqs::abstract_time<> ),
         decltype( std::ratio<30,2>{} * pqs::exponent10<3>{})
      >, double
   > q{20.0};

   using u = pqs::get_unit<decltype(q)>;
      
   using d = pqs::get_dimension<decltype(q)>;

   using v = pqs::get_numeric_type<decltype(q)>;

   using cf = pqs::get_conversion_factor<decltype(q)>;

   using s = pqs::get_measurement_system<decltype(q)>;
}