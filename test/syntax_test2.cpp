
#include <type_traits>
#include <pqs/meta/and.hpp>
#include <pqs/bits/base_dimension.hpp>

namespace pqs{

   template <typename TL, typename TR>
   inline
   constexpr
   typename std::enable_if<
      pqs::meta::and_<
         pqs::detail::is_base_dimension_ratio<TL>,
         pqs::detail::is_base_dimension_ratio<TR>
      >::value,
      typename detail::add_base_dimension_ratio<TL,TR>::type
   >::type
   operator * ( TL , TR )
   {
      return typename detail::add_base_dimension_ratio<TL,TR>::type{};
   }

}

#include "make_quantity.hpp"

#include <pqs/length.hpp>

#include <iostream>

using namespace pqs;

namespace {

   constexpr dim_mass<1> mass_dim;
   constexpr dim_length<1> length_dim;
   constexpr dim_time<1> time_dim;

}

void make_quantity_test()
{
   // create an anonymous si force type
   auto constexpr q = make_quantity<3>(
      mass_dim,   
      length_dim,
      time_dim * time_dim,  
      20.0
   );

   // compile fail , uncomment to test error message. Example error message below --->
  //  int x = q;
}
/*
-------------- Build: Quan in std_units (compiler: GNU GCC-9 Compiler)---------------

g++-9 -std=c++2a -fconcepts -Wno-literal-suffix -Wno-non-template-friend -Wno-stringop-overflow -Wno-pedantic -I/home___/pqs/src/include -c /home/___/pqs/test/syntax_test2.cpp -o obj/Debug/pqs/test/syntax_test2.o
/home/___/pqs/test/syntax_test2.cpp: In function ‘void make_quantity_test()’:
/home/___/pqs/test/syntax_test2.cpp:57:13: error: cannot convert ‘const pqs::quantity<pqs::unit<3, pqs::dim_mass<1>, pqs::dim_length<1>, pqs::dim_time<2> >, double>’ to ‘int’ in initialization
   57 |     int x = q;
      |             ^
      |             |
      |             const pqs::quantity<pqs::unit<3, pqs::dim_mass<1>, pqs::dim_length<1>, pqs::dim_time<2> >, double>
Process terminated with status 1 (0 minute(s), 11 second(s))
1 error(s), 0 warning(s) (0 minute(s), 11 second(s))
*/


