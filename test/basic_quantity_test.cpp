

#include <pqs/bits/base_quantities.hpp>

#include <pqs/instance/basic_quantity.hpp>
#include <pqs/bits/basic_unit.hpp>

struct dummy_system{};

void basic_quantity_test()
{
   pqs::basic_quantity<
      pqs::basic_unit<
         dummy_system,
         decltype(pqs::abstract_length<> / pqs::abstract_time<> ),
         decltype( std::ratio<3,2>{} * pqs::exponent10<3>{})
      >, double
   > x{20.0};
         
}