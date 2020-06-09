
#include <pqs/length.hpp>
#include <pqs/bits/base_quantities.hpp>
#include <pqs/meta/type_list.hpp>
#include <tuple>

using namespace pqs;


void quantity_syntax_test1() 
{

   auto qx = quantity<
      unit<
         3,          
         pqs::exp_length<1>, 
         pqs::exp_time<-1>,
         pqs::exp_mass<2>, 
         pqs::exp_temperature<3>
      >,
      double
   >{};
   
   // anonymous or r-value quantity
   auto qa = quantity<
      derived_unit<
         base_quantity_exp_list<
            pqs::exp_length<1>, 
            pqs::exp_time<-1>,
            pqs::exp_mass<2>, 
            pqs::exp_temperature<3>
         >, 3  //<-- exponent
      >,double
   > {};

   // named quantity
   auto qb = quantity<length_unit::mm, double>{};

   
   // alternative syntax
   auto qc = length::mm<>{};
  // non si unit
   auto qd = length::ft<>{};

  //int x = qc;

  // suppress set not used warnings
  (void) qx;
  (void) qa;
  (void) qb;
  (void) qc;
  (void) qd;

   // same type
  // qb = qx;

}