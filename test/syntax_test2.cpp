
#include <iostream>
#include <pqs/bits/quantity.hpp>
#include <pqs/bits/base_quantities.hpp>
#include "make_quantity.hpp"

using namespace pqs;

namespace {

   constexpr pqs::exp_mass<1> Mass;
   constexpr pqs::exp_length<1> Length;
   constexpr pqs::exp_time<1> Time;

   static_assert(pqs::is_base_quantity_exp<pqs::exp_length<1> >::value,"");
   static_assert(pqs::is_base_quantity_exp<pqs::exp_time<1> >::value,"");

   // these will be wrapped into a dimension e.g base_quantity_exp_list<base_length<1>,base_time<-1>
   constexpr auto Velocity = Length / Time; 
   constexpr auto Acceleration = Velocity / Time; 
   constexpr auto Force = Mass * Acceleration;
}

void make_quantity_test()
{
   auto q2 = make_quantity<-3>(
      Mass * Length / (Time * Time), 20.0
   );
   
   // alternative form
   auto constexpr q3 = quantity<
     make_unit<  // the unit will have form unit<3, dims... >)
       -3,
       decltype(Mass * Length / (Time * Time))
     >::type,
     double
   >{20.0};

   //q2 = q3; // check structural equality

   auto q4 = quantity<
     unit<  // the unit will have form unit<3, base_quantity_exp_list<dims...> >)
       -3,
       decltype(Mass * Length / (Time * Time))
     >,
     double
   >{20.0};

   //q2 = q4; // not structurally equal unit <I,D...> v unit<I,base_quantity_exp_list<D...> >
   (void) q4;

   auto q5 = quantity<make_unit<-3,decltype(Force)>::type,double>{20.0};

  // q2 = q5; // check structural equality

   // COMPILE FAIL To get type in error message
   //int x = q5;
}

