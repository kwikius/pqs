
#include <pqs/si/length.hpp>

namespace si = pqs::si;
using pqs::quantity;
using pqs::dimension;

void quantity_syntax_test1() 
{
   // anonymous or r-value quantity
   auto qa = quantity<
      si::unit<
         dimension<
            si::dim_length<1>, si::dim_time<-1>, si::dim_mass<2>, si::dim_temperature<3>
         >, 3
      >,double
   > {};

   auto qb = quantity<si::length_unit::mm, double>{};

   auto qc = si::length::mm<>{};

   auto qd = si::length::ft<>{};
   // same type
   qb = qc;

 //  qd = qa;  // error

  // should succeed once implemented
  // qd = qc;

}