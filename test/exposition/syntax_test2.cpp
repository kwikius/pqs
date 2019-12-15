
#include <iostream>
#include <pqs/bits/quantity.hpp>
#include "make_quantity.hpp"

#include <pqs/exposition/length.hpp>

using namespace pqs;
using namespace pqs_exposition;

namespace {

   constexpr dim_mass<1> mass_dim;
   constexpr dim_length<1> length_dim;
   constexpr dim_time<1> time_dim;

   static_assert(pqs::is_base_quantity_exp<dim_length<1> >::value,"");
   static_assert(pqs::is_base_quantity_exp<dim_time<1> >::value,"");

   // these will be wrapped into a dimension e.g dimension<dim_length<1>,dim_time<-1>
   constexpr auto velocity_dim = length_dim / time_dim; 
   constexpr auto acceleration_dim = velocity_dim / time_dim; 
   constexpr auto force_dim = mass_dim * acceleration_dim;
}

namespace pqs{

     template <int Exp, typename List>
     using make_unit = typename detail::make_unit<Exp,List>::type;
}

void make_quantity_test()
{

   auto q2 = make_quantity<-3>(
      mass_dim * length_dim / (time_dim * time_dim), 20.0
   );
   
   // alternative form
   auto constexpr q3 = quantity<
     make_unit<  // the unit will have form unit<3, dims... >)
       -3,
       decltype(mass_dim * length_dim / (time_dim * time_dim))
     >,
     double
   >{20.0};

   q2 = q3; // check structural equality

   auto q4 = quantity<
     unit<  // the unit will have form unit<3, dimension<dims...> >)
       -3,
       decltype(mass_dim * length_dim / (time_dim * time_dim))
     >,
     double
   >{20.0};

   //q2 = q4; // not structurally equal unit <I,D...> v unit<I,dimension<D...> >
   (void) q4;

   auto q5 = quantity<make_unit<-3,decltype(force_dim)>,double>{20.0};

   q2 = q5; // check structural equality

   // COMPILE FAIL To get type in error message
   //int x = q2;
}
/*

-------------- Build: Quan in std_units (compiler: GNU GCC-9 Compiler)---------------

g++-9 -std=c++2a -fconcepts -Wno-literal-suffix -Wno-non-template-friend -Wno-stringop-overflow -Wno-pedantic -I/home/andy/cpp/projects/std_units/pqs/src/include -I/home/andy/cpp/projects/quan-trunk -c /home/andy/cpp/projects/std_units/pqs/test/syntax_test2.cpp -o obj/Debug/pqs/test/syntax_test2.o
/home/andy/cpp/projects/std_units/pqs/test/syntax_test2.cpp: In function ‘void make_quantity_test()’:
/home/andy/cpp/projects/std_units/pqs/test/syntax_test2.cpp:232:12: error: cannot convert ‘const pqs::quantity<pqs::unit<-3, pqs::dim_length<1>, pqs::dim_time<-2>, pqs::dim_mass<1> >, double>’ to ‘int’ in initialization
  232 |    int x = q2;
      |            ^~
      |            |
      |            const pqs::quantity<pqs::unit<-3, pqs::dim_length<1>, pqs::dim_time<-2>, pqs::dim_mass<1> >, double>
Process terminated with status 1 (0 minute(s), 1 second(s))
1 error(s), 0 warning(s) (0 minute(s), 1 second(s))
 
*/




