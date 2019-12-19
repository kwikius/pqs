
#include <iostream>
#include <pqs/bits/quantity.hpp>
#include <pqs/bits/base_quantities.hpp>
#include "../make_quantity.hpp"

#include <pqs/exposition/length.hpp>

using namespace pqs;
using namespace pqs_exposition;

namespace {

   constexpr exp<base_mass,1> mass_dim;
   constexpr exp<base_length,1> length_dim;
   constexpr exp<base_time,1> time_dim;

   static_assert(pqs::is_base_quantity_exp<exp<base_length,1> >::value,"");
   static_assert(pqs::is_base_quantity_exp<exp<base_time,1> >::value,"");

   // these will be wrapped into a dimension e.g dimension<base_length<1>,base_time<-1>
   constexpr auto velocity_dim = length_dim / time_dim; 
   constexpr auto acceleration_dim = velocity_dim / time_dim; 
   constexpr auto force_dim = mass_dim * acceleration_dim;
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
     >::type,
     double
   >{20.0};

   //q2 = q3; // check structural equality

   auto q4 = quantity<
     unit<  // the unit will have form unit<3, dimension<dims...> >)
       -3,
       decltype(mass_dim * length_dim / (time_dim * time_dim))
     >,
     double
   >{20.0};

   //q2 = q4; // not structurally equal unit <I,D...> v unit<I,dimension<D...> >
   (void) q4;

   auto q5 = quantity<make_unit<-3,decltype(force_dim)>::type,double>{20.0};

  // q2 = q5; // check structural equality

   // COMPILE FAIL To get type in error message
   //int x = q5;
}

