

#include <pqs/bits/quantity.hpp>
#include <pqs/bits/dimension.hpp>
#include <pqs/bits/unit.hpp>
#include <pqs/bits/base_quantities.hpp>

#include <pqs/length.hpp>

namespace pqs{

   constexpr pqs::exp_mass<1> mass_v;
   constexpr pqs::exp_length<1> length_v;
   constexpr pqs::exp_time<1> time_v;  

}

using namespace pqs;

void quantity_syntax_test() 
{
   // short syntax
   auto constexpr qa = length::mm<>{};

   auto constexpr qb = length::ft<>{};
         
   // slightly more verbose syntax
   auto qc = quantity<length_unit::mm, double>{};

   // construct a quantity by composing dimension
   auto qd = quantity<
      si_unit<
         decltype( mass_v * length_v / pqs::pow<2,1>(time_v) ),
         unit_exp<-3>
      >
   >{20.0};

   // construct a si quantity from raw ingredients
   auto qe = quantity<
      si_unit<
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

   // construct a conversion unit to si quantity from raw ingredients
   auto qf = quantity<
      si_unit_conversion<
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
  // int x = qf;
  // suppress not used warnings
  (void) qa;
  (void) qb;
  (void) qc;
  (void) qd;
  (void) qe;
  (void) qf;

}