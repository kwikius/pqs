
#include <iostream>
#include <pqs/bits/quantity.hpp>
#include "make_quantity.hpp"
#include <pqs/meta/strip_cr.hpp>

using namespace pqs;

using pqs::meta::strip_cr;
using pqs::dimension;


template <typename T>
struct is_abstract_quantity :
pqs::meta::or_<
  
}{};


namespace {

   constexpr dim_mass<1> mass;
   constexpr dim_length<1> length;
   constexpr dim_time<1> time;
   constexpr auto velocity = length / time; 
   constexpr auto acceleration = velocity / time; 

   constexpr auto force = mass * acceleration;
//#################################################
   struct dim_torque : decltype(force * length){ /*typedef dim_torque type; */};
   struct dim_energy : decltype(force * length){ /*typedef dim_energy type; */};
//################################################
    
   // separate types...
   dim_torque torque;
   dim_energy energy;
}

int main()
{
   
   auto q1 = make_quantity<3>(torque,20.0);
   auto q2 = make_quantity<3>(energy,20.0);
}