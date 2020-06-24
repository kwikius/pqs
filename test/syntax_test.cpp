

#include <pqs/bits/base_quantities.hpp>
#include <pqs/concepts/dimension.hpp>
#include <pqs/si/length.hpp>
#include <pqs/si/speed.hpp>
#include <iostream>

#if ! defined  __cpp_inline_variables
namespace pqs{

   constexpr pqs::exp_mass<1> mass_v;

   constexpr pqs::exp_length<1> length_v;

   constexpr pqs::exp_time<1> time_v;  

}
#endif

using namespace pqs;

void custom_test1()
{

}
// derivation can be used to make a custom dimension
void custom_test2()
{
   struct  dim_velocity 
#if defined  __cpp_inline_variables
   : decltype(exp_length_v<1> / exp_time_v<1>) {};
#else
   : decltype(length_v / time_v) {};
#endif

   basic_quantity< 
      si::unit<dim_velocity,unit_exp<0> >, 
      double
   > v2;
}

void quantity_syntax_test() 
{

   custom_test1();
   custom_test2();

   // short syntax
   auto constexpr qa = si::length::mm<>{};  // si unit

   auto constexpr qaa = si::speed::m_per_s<>{};  // si unit

   auto constexpr qb = si::length::ft<>{};  // si unit conversion
         
   // slightly more verbose syntax
   auto qc = basic_quantity<si::length_unit::mm, double>{};

   // construct a quantity by composing dimension
   auto qd = basic_quantity<
      si::unit<
#if defined  __cpp_inline_variables
         decltype( exp_mass_v<1> * exp_length_v<1> / exp_time_v<2> ),
#else
         decltype( mass_v * length_v / pqs::pow<2,1>(time_v) ),
#endif
         unit_exp<-3>
      >
   >{20.0};

   // construct a si quantity from raw ingredients
   auto qe = basic_quantity<
      si::unit<
         base_quantity_exp_list<
            exp_length<1>,
            exp_time<-1>,
            exp_mass<2>,
            exp_temperature<3>
         >,
         unit_exp<3>
      >,
      double
   >{};

   // construct a si quantity conversion from raw ingredients
   auto qf = basic_quantity<
      si::unit_conversion<
         base_quantity_exp_list<
            exp_length<1>,
            exp_time<-1>,
            exp_mass<2>,
            exp_temperature<3>
         >,
         conversion_factor<
            std::ratio<100,394>,
            unit_exp<3>
         >
      >,
      double
   >{};

  //---------------------------------------------

  // uncomment to test how quantity appears in error message
  // int x = qd;
  // suppress not used warnings
  (void) qa;
  (void) qb;
  (void) qc;
  (void) qd;
  (void) qe;
  (void) qf;

}