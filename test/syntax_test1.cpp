
#include <pqs/length.hpp>

using namespace pqs;

void quantity_syntax_test1() 
{
   // anonymous or r-value quantity
   auto qa = quantity<
      unit<
         dimension<
            dim_length<1>, 
            dim_time<-1>,
            dim_mass<2>, 
            dim_temperature<3>
         >, 3
      >,double
   > {};

   auto qb = quantity<length_unit::mm, double>{};

   auto qc = length::mm<>{};

   auto qd = length::ft<>{};
   // same type
   qb = qc;

 //  qd = qa;  // error

  // should succeed once implemented
  // qd = qc;

}