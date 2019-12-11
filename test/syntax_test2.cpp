
#include <pqs/length.hpp>
#include <pqs/meta/type_list.hpp>
#include <tuple>

#include <iostream>

#include "make_quantity.hpp"

using namespace pqs;

void make_quantity_test()
{
   // create an anonymous si force type
   auto constexpr q = make_quantity<3>(
      dim_mass<1>{},   
      dim_length<1>{},
      dim_time<-2>{},  
      20.0
   );

   auto constexpr v = q.numeric_value();
   std::cout << v << '\n';

   // test error message see below --->
   // int x = q;
}
/*g++-9 -std=c++2a
 error: cannot convert ‘const pqs::quantity<pqs::unit<3, pqs::dim_mass<1>, pqs::dim_length<1>, pqs::dim_time<-2> >, double>’ to ‘int’ in initialization
   65 |    int x = q;
      |            ^
      |            |
      |            const pqs::quantity<pqs::unit<3, pqs::dim_mass<1>, pqs::dim_length<1>, pqs::dim_time<-2> >, double>
*/


