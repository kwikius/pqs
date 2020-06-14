

#include <pqs/bits/base_quantities.hpp>
#include <pqs/concepts/dimension.hpp>
#include <pqs/si/length.hpp>
#include <pqs/si/speed.hpp>

#if ! defined  __cpp_inline_variables
namespace pqs{

   constexpr pqs::exp_mass<1> mass_v;

   constexpr pqs::exp_length<1> length_v;

   constexpr pqs::exp_time<1> time_v;  

}
#endif

using namespace pqs;

void quantity_syntax_test() 
{
   // short syntax
   auto constexpr qa = length::mm<>{};

   auto constexpr qaa = speed::m_per_s<>{};

   auto constexpr qb = length::ft<>{};
         
   // slightly more verbose syntax
   auto qc = quantity<si::length_unit::mm, double>{};

   // construct a quantity by composing dimension
#if defined  __cpp_inline_variables
  auto qd = quantity<
      si::unit<
         decltype( exp_mass_v<1> * exp_length_v<1> / exp_time_v<2> ),
         unit_exp<-3>
      >
   >{20.0};
#else
   auto qd = quantity<
      si::unit<
         decltype( mass_v * length_v / pqs::pow<2,1>(time_v) ),
         unit_exp<-3>
      >
   >{20.0};
#endif
   // construct a si quantity from raw ingredients
   auto qe = quantity<
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
   auto qf = quantity<
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
   //int x = qaa;
  // suppress not used warnings
  (void) qa;
  (void) qb;
  (void) qc;
  (void) qd;
  (void) qe;
  (void) qf;

}